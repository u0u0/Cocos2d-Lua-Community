/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#include "ProgramCache.h"
#include "Device.h"
#include "ShaderModule.h"
#include "renderer/ccShaders.h"
#include "base/ccMacros.h"
#include "base/CCConfiguration.h"

namespace std
{
    template <>
    struct hash<cocos2d::backend::ProgramType>
    {
        typedef cocos2d::backend::ProgramType argument_type;
        typedef std::size_t result_type;
        result_type operator()(argument_type const& v) const
        {
            return hash<int>()(static_cast<int>(v));
        }
    };
}

CC_BACKEND_BEGIN

std::unordered_map<backend::ProgramType, backend::Program*>  ProgramCache::_cachedPrograms;
ProgramCache* ProgramCache::_sharedProgramCache = nullptr;

ProgramCache* ProgramCache::getInstance()
{
    if(!_sharedProgramCache)
    {
        _sharedProgramCache = new (std::nothrow) ProgramCache();
        if(!_sharedProgramCache->init())
        {
            CC_SAFE_RELEASE(_sharedProgramCache);
        }
    }
    return _sharedProgramCache;
}

void ProgramCache::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedProgramCache);
}

ProgramCache::~ProgramCache()
{
    for(auto& program : _cachedPrograms)
    {
        CC_SAFE_RELEASE(program.second);
    }
    CCLOGINFO("deallocing ProgramCache: %p", this);
    ShaderCache::destroyInstance();
}

bool ProgramCache::init()
{
    addProgram(ProgramType::POSITION_TEXTURE_COLOR);
    addProgram(ProgramType::ETC1);
    addProgram(ProgramType::LABEL_DISTANCE_NORMAL);
    addProgram(ProgramType::LABEL_NORMAL);
    addProgram(ProgramType::LABLE_OUTLINE);
    addProgram(ProgramType::LABLE_DISTANCEFIELD_GLOW);
    addProgram(ProgramType::POSITION_COLOR_LENGTH_TEXTURE);
    addProgram(ProgramType::POSITION_COLOR_TEXTURE_AS_POINTSIZE);
    addProgram(ProgramType::POSITION_COLOR);
    addProgram(ProgramType::POSITION);
    addProgram(ProgramType::LAYER_RADIA_GRADIENT);
    addProgram(ProgramType::POSITION_TEXTURE);
    addProgram(ProgramType::POSITION_TEXTURE_COLOR_ALPHA_TEST);
    addProgram(ProgramType::POSITION_UCOLOR);
    addProgram(ProgramType::ETC1_GRAY);
    addProgram(ProgramType::GRAY_SCALE);
    addProgram(ProgramType::CAMERA_CLEAR);
    return true;
}

void ProgramCache::addProgram(ProgramType type)
{
    Program* program = nullptr;
    switch (type) {
        case ProgramType::POSITION_TEXTURE_COLOR:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, positionTextureColor_frag);
            break;
        case ProgramType::ETC1:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, etc1_frag);
            break;
        case ProgramType::LABEL_DISTANCE_NORMAL:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, label_distanceNormal_frag);
            break;
        case ProgramType::LABEL_NORMAL:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, label_normal_frag);
            break;
        case ProgramType::LABLE_OUTLINE:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, labelOutline_frag);
            break;
        case ProgramType::LABLE_DISTANCEFIELD_GLOW:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, labelDistanceFieldGlow_frag);
            break;
        case ProgramType::POSITION_COLOR_LENGTH_TEXTURE:
            program = backend::Device::getInstance()->newProgram(positionColorLengthTexture_vert, positionColorLengthTexture_frag);
            break;
        case ProgramType::POSITION_COLOR_TEXTURE_AS_POINTSIZE:
            program = backend::Device::getInstance()->newProgram(positionColorTextureAsPointsize_vert, positionColor_frag);
            break;
        case ProgramType::POSITION_COLOR:
            program = backend::Device::getInstance()->newProgram(positionColor_vert, positionColor_frag);
            break;
        case ProgramType::POSITION:
            program = backend::Device::getInstance()->newProgram(position_vert, positionColor_frag);
            break;
        case ProgramType::LAYER_RADIA_GRADIENT:
            program = backend::Device::getInstance()->newProgram(position_vert, layer_radialGradient_frag);
            break;
        case ProgramType::POSITION_TEXTURE:
            program = backend::Device::getInstance()->newProgram(positionTexture_vert, positionTexture_frag);
            break;
        case ProgramType::POSITION_TEXTURE_COLOR_ALPHA_TEST:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, positionTextureColorAlphaTest_frag);
            break;
        case ProgramType::POSITION_UCOLOR:
            program = backend::Device::getInstance()->newProgram(positionUColor_vert, positionUColor_frag);
            break;
        case ProgramType::ETC1_GRAY:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, etc1Gray_frag);
            break;
        case ProgramType::GRAY_SCALE:
            program = backend::Device::getInstance()->newProgram(positionTextureColor_vert, grayScale_frag);
            break;
        case ProgramType::CAMERA_CLEAR:
            program = backend::Device::getInstance()->newProgram(cameraClear_vert, cameraClear_frag);
            break;
        default:
            CCASSERT(false, "Not built-in program type.");
            break;
    }
    program->setProgramType(type);
    ProgramCache::_cachedPrograms.emplace(type, program);
}

backend::Program* ProgramCache::getBuiltinProgram(ProgramType type) const
{
    const auto& iter = ProgramCache::_cachedPrograms.find(type);
    if (ProgramCache::_cachedPrograms.end() != iter)
    {
        return iter->second;
    }
    return nullptr;
}

void ProgramCache::removeProgram(backend::Program* program)
{
    if (!program)
    {
        return;
    }
    
    for (auto it = _cachedPrograms.cbegin(); it != _cachedPrograms.cend();)
    {
        if (it->second == program)
        {
            it->second->release();
            it = _cachedPrograms.erase(it);
            break;
        }
        else
            ++it;
    }
}

void ProgramCache::removeUnusedProgram()
{
    for (auto iter = _cachedPrograms.cbegin(); iter != _cachedPrograms.cend();)
    {
        auto program = iter->second;
        if (program->getReferenceCount() == 1)
        {
//            CCLOG("cocos2d: TextureCache: removing unused program");
            program->release();
            iter = _cachedPrograms.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void ProgramCache::removeAllPrograms()
{
    for (auto& program : _cachedPrograms)
    {
        program.second->release();
    }
    _cachedPrograms.clear();
}

CC_BACKEND_END
