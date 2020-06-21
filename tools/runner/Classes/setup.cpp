// Copyright 2020 KeNan Liu
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

#ifdef _WINDOWS
#undef _UNICODE
#include "../proj.win32/getopt.h"
#else
#include <getopt.h>
#endif

#include "setup.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

// singleton
static CommandSetup *s_instance = nullptr;

CommandSetup::CommandSetup()
: _logToFile(false)
, _scale(100)
, _width(960)
, _height(640)
, _relauncher(nullptr)
{
}

CommandSetup::~CommandSetup()
{
}

CommandSetup* CommandSetup::getInstance()
{
    if (!s_instance) {
        s_instance = new (std::nothrow) CommandSetup();
        s_instance->init();
    }
    return s_instance;
}

void CommandSetup::init(void)
{
    // setup hotkeys
    auto keyEvent = cocos2d::EventListenerKeyboard::create();
    keyEvent->onKeyReleased = [&](EventKeyboard::KeyCode key, Event*) {
        if (key == EventKeyboard::KeyCode::KEY_F5) {
            std::string cmdLine = makeCommand();
            _relauncher(cmdLine);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(keyEvent, 1);
}

void CommandSetup::setRelauncher(RELAUNCHER cb)
{
    _relauncher = cb;
}

void CommandSetup::setEngineRootPath(std::string root)
{
    _engineRootPath = root;
}

// example short:
// -w 1136 -h 640 -s 75 -l -g /newprj -r /newprj/output
// example long:
// --width 1136 --height 640 --scale 75 --log --gamedir /newprj --writedir /newprj/output
void CommandSetup::parseCommand(int argc, char *argv[])
{
    // parse opts
    int ch;
    int optIndex = 0;
    struct option long_options[] = {
        {"width"   , required_argument, NULL, 'w'},
        {"height"  , required_argument, NULL, 'h'},
        {"scale"   , required_argument, NULL, 's'},
        {"log"     , no_argument      , NULL, 'l'},
        {"gamedir" , required_argument, NULL, 'g'},
        {"writedir", required_argument, NULL, 'r'},
    };
    while((ch = getopt_long(argc, (char * const *)argv, "w:h:s:lg:r:", long_options, &optIndex)) != -1) {
        switch(ch) {
            case 'l': // -l
                _logToFile = true;
                break;
            case 'w': // -w 1136
                _width = atoi(optarg);
                break;
            case 'h': // -h 640
                _height = atoi(optarg);
                break;
            case 's': // -s 75
                _scale = atoi(optarg);
                break;
            case 'g': // -g "/gamedir"
                _gameRootPath = optarg;
                break;
            case 'r': // -r "/writedir"
                _writePath = optarg;
                break;
            default:
                printf("unknow option :%c\n", ch);
        }
    }
    
    // init writePath
    if (_writePath.size() == 0) {
        if (_gameRootPath.size() > 0) {
            _writePath = _gameRootPath;
        } else {
            _writePath = _engineRootPath;
        }
    }
    
    // parse args, not in use yet
    while (optind < argc) {
        printf("arg:%s\n", argv[optind]);
        optind++;
    }
}

std::string CommandSetup::makeCommand(void)
{
    stringstream stream;
    
    stream << "-w ";
    stream << _width;
    
    stream << " -h ";
    stream << _height;
    
    stream << " -s ";
    stream << _scale;
    
    if (_gameRootPath.size() > 0) {
        stream << " -g ";
        stream << _gameRootPath;
    }
    
    if (_writePath.size() > 0) {
        stream << " -r ";
        stream << _writePath;
    }
    
    if (_logToFile) {
        stream << " -l";
    }
    
    return stream.str();
}

void CommandSetup::setupEngine(void)
{
    printf("=== begin setup configs ===\n");
    printf("logToFile:%s\n", _logToFile ? "true" : "false");
    printf("scale:%f\n", _scale / 100.0);
    printf("size:%dx%d\n", _width, _height);
    printf("writePath:%s\n", _writePath.c_str());
    printf("gameRootPath:%s\nisDirectoryExist: %s\n", _gameRootPath.c_str(), (_gameRootPath.size() > 0 && FileUtils::getInstance()->isDirectoryExist(_gameRootPath)) ? "TRUE" : "FALSE");
    printf("engineRootPath:%s\nisDirectoryExist: %s\n", _engineRootPath.c_str(), FileUtils::getInstance()->isDirectoryExist(_engineRootPath) ? "TRUE" : "FALSE");
    printf("=== end setup configs ===\n");
    
    if (_gameRootPath.size() > 0) {
        // load game
        std::vector<std::string> paths;
        paths.push_back(_gameRootPath);
        FileUtils::getInstance()->setDefaultResourceRootPath(_gameRootPath);
        FileUtils::getInstance()->setSearchPaths(paths);
    } else {
        // load engine default test cases.
        std::vector<std::string> paths;
        paths.push_back(_engineRootPath + "tests");
        paths.push_back(_engineRootPath + "templates");
        FileUtils::getInstance()->setDefaultResourceRootPath(paths[0]);
        FileUtils::getInstance()->setSearchPaths(paths);
    }
    
    FileUtils::getInstance()->setWritablePath(_writePath);
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = cocos2d::GLViewImpl::createWithRect("LuaGameRunner", Rect(0, 0, _width, _height), _scale / 100.0f);
        director->setOpenGLView(glview);
        director->startAnimation();
    }
}

std::string CommandSetup::getLogPath()
{
    if (!_logToFile) {
        return "";
    }
    
    std::string logFileName = "debug.log";
    char lastChar = _writePath[_writePath.length() - 1];
    if (lastChar == '/' || lastChar == '\\') {
        return _writePath + logFileName;
    }
    
    return _writePath + "/" + logFileName;
}
