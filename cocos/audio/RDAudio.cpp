// Copyright 2016 KeNan Liu
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory.h>

#include "platform/CCFileUtils.h"
#include "cocos/audio/RDAudio.h"
#include "cocos/audio/RDAudioOgg.h"
#include "cocos2d.h"

// singleton stuff
RDAudio *RDAudio::s_instant = nullptr;

RDAudio::RDAudio()
: _device(nullptr)
, _context(nullptr)
, _needQuit(false)
, _asyncRefCount(0)
, _thread(nullptr)
{
}

RDAudio::~RDAudio()
{
    if (_context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(_context);
    }
    if (_device) {
        alcCloseDevice(_device);
    }
    if (_thread) {
        _thread->join();
        delete _thread;
    }
}

RDAudio *RDAudio::getInstance()
{
    if (!s_instant) {
        s_instant = new (std::nothrow) RDAudio();
        s_instant->init();
    }
    
    return s_instant;
}

void RDAudio::destroyInstance()
{
    if (s_instant) {
        s_instant->waitForQuit();
        delete s_instant;
        s_instant = nullptr;
    }
}

void RDAudio::pause()
{
//#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    alcMakeContextCurrent(NULL);
    alcSuspendContext(_context);
//#endif
}

void RDAudio::resume()
{
//#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    alcMakeContextCurrent(_context);
    alcProcessContext(_context);
//#endif
}

void RDAudio::waitForQuit()
{
    // notify sub thread to quick
    _needQuit = true;
    _inCondition.notify_one();
    if (_thread) {
        _thread->join();
    }
}

void RDAudio::init(void)
{
    // Initialization device
    const ALCchar *name = NULL;
    if (!_device) {
        // select the "preferred device"
        _device = alcOpenDevice(NULL);
        if (!_device) {
            cocos2d::log("Error: alcOpenDevice Could not open a device!");
            return;
        }
        _context = alcCreateContext(_device, NULL);
        if(_context == NULL || alcMakeContextCurrent(_context) == ALC_FALSE) {
            if(_context != NULL) {
                alcDestroyContext(_context);
            }
            alcCloseDevice(_device);
            cocos2d::log("Error: alcMakeContextCurrent Could not set a context!!");
            return;
        }
        if(alcIsExtensionPresent(_device, "ALC_ENUMERATE_ALL_EXT")) {
            name = alcGetString(_device, ALC_ALL_DEVICES_SPECIFIER);
        }
        if(!name || alcGetError(_device) != AL_NO_ERROR) {
            name = alcGetString(_device, ALC_DEVICE_SPECIFIER);
        }
        cocos2d::log("alcOpenDevice Opened \"%s\"", name);
       // start audio decode thread
        _thread = new std::thread(&RDAudio::threadLoop, this);
    }
}

void RDAudio::threadLoop()
{
    AsyncStruct *asyncStruct = nullptr;
    
    while (true) {
        std::unique_lock<std::mutex> lock(_inMutex);
        // deal with fade notify
        while (_inQueue.empty()) {
            // ONLY exit while the queue is empty
            if (_needQuit) {
                lock.unlock();
                return;
            }
            _inCondition.wait(lock);
        }
        
        asyncStruct = _inQueue.front();
        _inQueue.pop();
        lock.unlock();
        
        // decode
        cocos2d::Data data = cocos2d::FileUtils::getInstance()->getDataFromFile(asyncStruct->filename);
        if (data.getSize() > 0) {
            int rtn = decodeOgg(data.getBytes(),
                                data.getSize(),
                                &asyncStruct->pcmData,
                                &asyncStruct->channels,
                                &asyncStruct->rate,
                                &asyncStruct->size);
            if (rtn < 0) {
                if (asyncStruct->pcmData) {
                    free(asyncStruct->pcmData);
                    // set to NULL for main thread error check
                    asyncStruct->pcmData = NULL;
                }
            }
        }
        
        // add to outQueue
        _outMutex.lock();
        _outQueue.push(asyncStruct);
        _outMutex.unlock();
    }
}

void RDAudio::scheduleLoop(float)
{
    AsyncStruct *asyncStruct = nullptr;
    
    _outMutex.lock();
    if (_outQueue.empty())
    {
        _outMutex.unlock();
        return;
    }
    
    asyncStruct = _outQueue.front();
    _outQueue.pop();
    _outMutex.unlock();
    
    // create OpenAL buffer
    ALuint bufferID = 0;
    if (asyncStruct->pcmData) {
        // clear old error
        alGetError();
        alGenBuffers(1, &bufferID);
        if (alGetError() != AL_NO_ERROR) {
            cocos2d::log("Error: RDAudio_LoadFile can't gen OpenAL Buffer");
            bufferID = 0;
        } else {
            ALenum format = (asyncStruct->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
            alBufferData(bufferID, format, asyncStruct->pcmData, asyncStruct->size, asyncStruct->rate);
            if (alGetError() != AL_NO_ERROR) {
                cocos2d::log("Error: RDAudio_LoadFile alBufferData Fail");
                alDeleteBuffers(1, &bufferID);
                bufferID = 0;
            }
        }
    } else {
        cocos2d::log("Fail to decode file: %s, ONLY support ogg now!", asyncStruct->filename.c_str());
    }
    // callback to lua
    asyncStruct->cb(asyncStruct->funcID, bufferID);
    // free memory
    delete asyncStruct;
    
    // remove task in main thread
    --_asyncRefCount;
    if (0 == _asyncRefCount)
    {
        cocos2d::Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(RDAudio::scheduleLoop), this);
    }
}

void RDAudio::loadFileAsyn(const char *filename, int funcID, AudioCallback cb)
{
    // add task in main thread
    if (0 == _asyncRefCount) {
        cocos2d::Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(RDAudio::scheduleLoop), this, 0, false);
    }
    ++_asyncRefCount;
    
    // add task in sub thread
    AsyncStruct *asyncStruct = new (std::nothrow) AsyncStruct(filename, funcID, cb);
    std::unique_lock<std::mutex> lock(_inMutex);
    _inQueue.push(asyncStruct);
    lock.unlock();
    
    // weak up sub thread
    _inCondition.notify_one();
}
