/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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
#include "scripting/lua-bindings/manual/extension/lua_cocos2dx_extension_manual.h"
#include "scripting/lua-bindings/auto/lua_cocos2dx_extension_auto.hpp"

#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "cocos-ext.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"

USING_NS_CC;


int lua_cocos2dx_extension_ParticleSystem3D_getParticlePool(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystem3D* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystem3D",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ParticleSystem3D*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ParticleSystem3D_getParticlePool'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ParticleSystem3D_getParticlePool'", nullptr);
            return 0;
        }
        const cocos2d::ParticlePool& ret = cobj->getParticlePool();
        tolua_pushusertype(tolua_S,(void*)&ret, "cc.ParticlePool");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystem3D:getParticlePool",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ParticleSystem3D_getParticlePool'.",&tolua_err);
#endif
    
    return 0;
}

static void extendParticleSystem3D(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.ParticleSystem3D");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "getParticlePool", lua_cocos2dx_extension_ParticleSystem3D_getParticlePool);
    }
    lua_pop(tolua_S, 1);
}

int lua_cocos2dx_extension_ParticlePool_getActiveDataList(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticlePool* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticlePool",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::ParticlePool*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extension_ParticlePool_getActiveDataList'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_extension_ParticlePool_getActiveDataList'", nullptr);
            return 0;
        }
        const ParticlePool::PoolList& ret = cobj->getActiveDataList();
        
        lua_newtable(tolua_S);
        if (ret.empty())
            return 1;
        
        int index = 1;
        for (const auto& obj : ret)
        {
            if (nullptr == obj)
                continue;
            
            lua_pushnumber(tolua_S, (lua_Number)index);
            tolua_pushusertype(tolua_S,(void*)&ret, "cc.ParticlePool");
            lua_rawset(tolua_S, -3);
            ++index;
        }
        
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticlePool:getActiveParticleList",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extension_ParticlePool_getActiveParticleList'.",&tolua_err);
#endif
    
    return 0;
}

static void extendParticlePool(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "cc.ParticlePool");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "getActiveDataList", lua_cocos2dx_extension_ParticlePool_getActiveDataList);
    }
    lua_pop(tolua_S, 1);
}

int register_all_cocos2dx_extension_manual(lua_State* tolua_S)
{
    extendParticleSystem3D(tolua_S);
    extendParticlePool(tolua_S);
    return 0;
}

int register_extension_module(lua_State* tolua_S)
{
    lua_getglobal(tolua_S, "_G");
    if (lua_istable(tolua_S,-1))//stack:...,_G,
    {
        register_all_cocos2dx_extension(tolua_S);
        register_all_cocos2dx_extension_manual(tolua_S);
    }
    lua_pop(tolua_S, 1);
    return 1;
}
