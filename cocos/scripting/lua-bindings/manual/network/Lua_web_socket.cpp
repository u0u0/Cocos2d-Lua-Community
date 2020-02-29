/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2020 cocos2d-lua.org
 
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

#include <map>
#include <string>

#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/network/Lua_web_socket.h"

#include "scripting/lua-bindings/manual/CCLuaStack.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"

using namespace cocos2d;

LuaWebSocket::~LuaWebSocket()
{
	ScriptHandlerMgr::getInstance()->removeObjectAllHandlers((void*)this);
}

void LuaWebSocket::onOpen(WebSocket* ws)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this, ScriptHandlerMgr::HandlerType::WEBSOCKET_OPEN);
    if (0 != handler) {
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        if (stack) {
            stack->executeFunctionByHandler(handler, 0);
        }
    }
}

void LuaWebSocket::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this,ScriptHandlerMgr::HandlerType::WEBSOCKET_MESSAGE);
    if (0 != handler) {
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        if (stack) {
            stack->pushString(data.bytes, (int)data.len);
            stack->executeFunctionByHandler(handler, 1);
        }
    }
}

void LuaWebSocket::onClose(WebSocket* ws)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this,ScriptHandlerMgr::HandlerType::WEBSOCKET_CLOSE);
    if (0 != handler) {
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        if (stack) {
            stack->executeFunctionByHandler(handler, 0);
        }
    }
}

void LuaWebSocket::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{
	LuaWebSocket* luaWs = dynamic_cast<LuaWebSocket*>(ws);
	if (NULL != luaWs) {
		int handler = ScriptHandlerMgr::getInstance()->getObjectHandler((void*)this,ScriptHandlerMgr::HandlerType::WEBSOCKET_ERROR);
		if (0 != handler)
		{
            LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
            if (stack) {
                stack->pushInt((int)error);
                stack->executeFunctionByHandler(handler, 1);
            }
		}
	}
}

static int tolua_collect_WebSocket (lua_State* tolua_S)
{
	LuaWebSocket *self = (LuaWebSocket *)tolua_tousertype(tolua_S, 1, 0);
    delete self;
	return 0;
}

static int tolua_Cocos2d_WebSocket_create(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif

	int argumentCount = lua_gettop(tolua_S);
	if (argumentCount >= 2) {
		std::string url;
		std::vector<std::string> protocols;
		std::string caCertPath;

#if COCOS2D_DEBUG >= 1
		if (!tolua_isusertable(tolua_S, 1, "cc.WebSocket", 0, &tolua_err) ||
				!tolua_isstring(tolua_S, 2, 0, &tolua_err)
		   )
			goto tolua_lerror;
#endif
		if (argumentCount == 3) {
			if (lua_istable(tolua_S, 3)) {
				luaval_to_std_vector_string(tolua_S, 3, &protocols, "cc.WebSocket.create");
			} else if (lua_isstring(tolua_S, 3)) {
				luaval_to_std_string(tolua_S, 3, &caCertPath);
			} else {
				luaL_error(tolua_S, "The second parameter should be a table contains protocols of string type or a string indicates ca certificate path!");
				return 0;
			}
		} else if (argumentCount == 4) {
#if COCOS2D_DEBUG >= 1
			if (!tolua_istable(tolua_S, 3, 0, &tolua_err)
					|| !tolua_isstring(tolua_S, 4, 0, &tolua_err))
				goto tolua_lerror;
#endif

			luaval_to_std_vector_string(tolua_S, 3, &protocols, "cc.WebSocket.create");
			luaval_to_std_string(tolua_S, 4, &caCertPath);
		}

		luaval_to_std_string(tolua_S, 2, &url);

		LuaWebSocket *wSocket = new (std::nothrow) LuaWebSocket();
		wSocket->init(*wSocket, url, &protocols, caCertPath);
		tolua_pushusertype(tolua_S, (void*)wSocket, "cc.WebSocket");
		tolua_register_gc(tolua_S,lua_gettop(tolua_S));
		return 1;
	}
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
#endif
	return 0;
}

static int tolua_Cocos2d_WebSocket_createByAProtocol(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"cc.WebSocket",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err)  ||
			!tolua_isstring(tolua_S,3,0,&tolua_err)  ||
			!tolua_isnoobj(tolua_S,4,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		const char *urlName  = (const char*)tolua_tostring(tolua_S,2,0);
		const char *protocol = (const char*)tolua_tostring(tolua_S,3,0);
		std::vector<std::string> protocols;
		protocols.push_back(protocol);
		LuaWebSocket *wSocket = new (std::nothrow) LuaWebSocket();
		wSocket->init(*wSocket, urlName, &protocols);
		tolua_pushusertype(tolua_S,(void*)wSocket,"cc.WebSocket");
		tolua_register_gc(tolua_S,lua_gettop(tolua_S));
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'createByAProtocol'.",&tolua_err);
	return 0;
#endif
}

static int tolua_Cocos2d_WebSocket_getReadyState(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"cc.WebSocket",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		LuaWebSocket *self = (LuaWebSocket*)tolua_tousertype(tolua_S,1,0);
		int tolua_ret = -1;
		if (NULL != self) {
			tolua_ret = (int)self->getReadyState();
		}
		tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getReadyState'.",&tolua_err);
	return 0;
#endif
}

static int tolua_Cocos2d_WebSocket_close(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"cc.WebSocket",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		LuaWebSocket *self = (LuaWebSocket*)tolua_tousertype(tolua_S, 1, 0);
		if (NULL != self ) {
			self->closeAsync();
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getReadyState'.",&tolua_err);
	return 0;
#endif
}

static int tolua_Cocos2d_WebSocket_sendString(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S, 1, "cc.WebSocket", 0, &tolua_err) ||
			!tolua_isstring(tolua_S, 2, 0, &tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		LuaWebSocket *self = (LuaWebSocket*)tolua_tousertype(tolua_S, 1, 0);
		size_t size = 0;
		const char *data = (const char*)lua_tolstring(tolua_S, 2, &size);
        bool isBinary = lua_toboolean(tolua_S, 3);
        if ( NULL == data)
            return 0;
		if (isBinary || strlen(data) != size) {
			self->send((const unsigned char*)data, (unsigned int)size);
		} else {
			self->send(data);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'sendString'.",&tolua_err);
	return 0;
#endif
}

static int websocket_url_getter(lua_State* L)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.WebSocket", 0, &tolua_err))
		goto tolua_lerror;
	else
#endif
	{
		LuaWebSocket* self = (LuaWebSocket*)tolua_tousertype(L, 1, 0);
		lua_pushstring(L, self->getUrl().c_str());
		return 1;
	}
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L,"#ferror in function 'sendString'.",&tolua_err);
	return 0;
#endif
}

static int websocket_protocol_getter(lua_State* L)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (!tolua_isusertype(L, 1, "cc.WebSocket", 0, &tolua_err))
		goto tolua_lerror;
	else
#endif
	{
		LuaWebSocket* self = (LuaWebSocket*)tolua_tousertype(L, 1, 0);
		lua_pushstring(L, self->getProtocol().c_str());
		return 1;
	}
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(L,"#ferror in function 'sendString'.",&tolua_err);
	return 0;
#endif
}

int tolua_Cocos2d_WebSocket_registerScriptHandler(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
            !tolua_isusertype(tolua_S,1,"cc.WebSocket",0,&tolua_err) ||
            !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) ||
            !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
            !tolua_isnoobj(tolua_S,4,&tolua_err)
       )
        goto tolua_lerror;
    else
#endif
    {
        LuaWebSocket* self = (LuaWebSocket*)tolua_tousertype(tolua_S,1,0);
        if (NULL != self ) {
            int handler = toluafix_ref_function(tolua_S,2,0);
            ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType)(int)tolua_tonumber(tolua_S,3,0);
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, handlerType);
        }
    }
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
    return 0;
#endif
}

int tolua_Cocos2d_WebSocket_unregisterScriptHandler(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (
            !tolua_isusertype(tolua_S,1,"cc.WebSocket",0,&tolua_err) ||
            !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
            !tolua_isnoobj(tolua_S,3,&tolua_err)
       )
        goto tolua_lerror;
    else
#endif
    {
        LuaWebSocket* self = (LuaWebSocket*)tolua_tousertype(tolua_S,1,0);
        if (NULL != self ) {
            ScriptHandlerMgr::HandlerType handlerType = (ScriptHandlerMgr::HandlerType)(int)tolua_tonumber(tolua_S,2,0);
            ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, handlerType);
        }
    }
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
    return 0;
#endif
}

TOLUA_API int register_web_socket_manual(lua_State* tolua_S){
	tolua_open(tolua_S);
	tolua_usertype(tolua_S, "cc.WebSocket");
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");
	tolua_cclass(tolua_S,"WebSocket","cc.WebSocket","",tolua_collect_WebSocket);
	tolua_beginmodule(tolua_S,"WebSocket");
	tolua_function(tolua_S, "create", tolua_Cocos2d_WebSocket_create);
	tolua_function(tolua_S, "createByAProtocol", tolua_Cocos2d_WebSocket_createByAProtocol);
	tolua_function(tolua_S, "getReadyState", tolua_Cocos2d_WebSocket_getReadyState);
	tolua_function(tolua_S, "close", tolua_Cocos2d_WebSocket_close);
	tolua_function(tolua_S, "sendString", tolua_Cocos2d_WebSocket_sendString);
    tolua_function(tolua_S, "registerScriptHandler", tolua_Cocos2d_WebSocket_registerScriptHandler);
    tolua_function(tolua_S, "unregisterScriptHandler", tolua_Cocos2d_WebSocket_unregisterScriptHandler);
	tolua_variable(tolua_S, "url", websocket_url_getter, nullptr);
	tolua_variable(tolua_S, "protocol", websocket_protocol_getter, nullptr);
	tolua_endmodule(tolua_S);
	tolua_endmodule(tolua_S);
	return 1;
}
