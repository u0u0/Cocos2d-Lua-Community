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

#include <map>
#include <string>

#include "network/AsyncTCP.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"

#include "scripting/lua-bindings/manual/CCLuaStack.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"

using namespace cocos2d;

static int lua_AsyncTCP_create(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertable(tolua_S, 1, "AsyncTCP", 0, &tolua_err)) goto tolua_lerror;
#endif

    do {
        AsyncTCP *asyncTCP = new (std::nothrow) AsyncTCP();
        tolua_pushusertype(tolua_S, (void*)asyncTCP, "AsyncTCP");
        tolua_register_gc(tolua_S, lua_gettop(tolua_S));
        return 1;
    } while (0);
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AsyncTCP_create'.",&tolua_err);
    return 0;
#endif
}

static int lua_AsyncTCP_setEventCB(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "AsyncTCP", 0, &tolua_err)
        || !toluafix_isfunction(tolua_S, 2, "LUA_FUNCTION", 0, &tolua_err))
        goto tolua_lerror;
#endif
    do {
        AsyncTCP *self = (AsyncTCP *)tolua_tousertype(tolua_S, 1, 0);
        if (self) {
            int handler = toluafix_ref_function(tolua_S, 2, 0);

            self->setEventCB([=](int state, unsigned char *buff, size_t size) {
                LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
                stack->pushInt(state);
                if (buff) {
                    stack->pushString((const char*)buff, size);
                } else {
                    stack->pushNil();
                }
                stack->executeFunctionByHandler(handler, 2);
            });
            
            ScriptHandlerMgr::getInstance()->removeObjectAllHandlers((void*)self);
            ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        }
        return 0;
    } while (0);
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AsyncTCP_setEventCB'.", &tolua_err);
    return 0;
#endif
}

static int lua_AsyncTCP_open(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "AsyncTCP", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err)
        || !tolua_isnumber(tolua_S, 3, 0, &tolua_err))
        goto tolua_lerror;
#endif
    do {
        AsyncTCP *self = (AsyncTCP *)tolua_tousertype(tolua_S, 1, 0);
        if (self) {
            const char *host = lua_tostring(tolua_S, 2);
            int port = lua_tointeger(tolua_S, 3);
            if (lua_isnumber(tolua_S, 4)) {
                self->open(host, port, lua_tointeger(tolua_S, 4));
            } else {
                self->open(host, port);
            }
        }
        return 0;
    } while (0);
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AsyncTCP_open'.", &tolua_err);
    return 0;
#endif
}

static int lua_AsyncTCP_send(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "AsyncTCP", 0, &tolua_err)
        || !tolua_isstring(tolua_S, 2, 0, &tolua_err))
        goto tolua_lerror;
#endif
    do {
        AsyncTCP *self = (AsyncTCP *)tolua_tousertype(tolua_S, 1, 0);
        if (self) {
            const char *data = lua_tostring(tolua_S, 2);
            size_t size = lua_objlen(tolua_S, 2);
            self->send((unsigned char *)data, size);
        }
        return 0;
    } while (0);
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AsyncTCP_send'.", &tolua_err);
    return 0;
#endif
}

static int lua_AsyncTCP_close(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(tolua_S, 1, "AsyncTCP", 0, &tolua_err))
        goto tolua_lerror;
#endif
    do {
        AsyncTCP *self = (AsyncTCP *)tolua_tousertype(tolua_S, 1, 0);
        if (self) {
            self->close();
        }
        return 0;
    } while (0);
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_AsyncTCP_close'.", &tolua_err);
    return 0;
#endif
}

static int lua_gc_AsyncTCP(lua_State* tolua_S)
{
    AsyncTCP *self = (AsyncTCP *)tolua_tousertype(tolua_S, 1, 0);
    ScriptHandlerMgr::getInstance()->removeObjectAllHandlers((void*)self);
    delete self;
    return 0;
}

TOLUA_API int register_AsyncTCP_manual(lua_State* tolua_S)
{
    AsyncTCP::initEnv(); // init library
    
	tolua_open(tolua_S);
	tolua_usertype(tolua_S, "AsyncTCP");
	tolua_cclass(tolua_S, "AsyncTCP", "AsyncTCP", "cc.Ref", lua_gc_AsyncTCP);
	tolua_beginmodule(tolua_S, "AsyncTCP");
	tolua_function(tolua_S, "create", lua_AsyncTCP_create);
    tolua_function(tolua_S, "setEventCB", lua_AsyncTCP_setEventCB);
    tolua_function(tolua_S, "open", lua_AsyncTCP_open);
    tolua_function(tolua_S, "send", lua_AsyncTCP_send);
    tolua_function(tolua_S, "close", lua_AsyncTCP_close);
	tolua_endmodule(tolua_S);
	return 1;
}
