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
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/network/lua_cocos2dx_network_manual.h"
#include "scripting/lua-bindings/manual/network/lua_extensions.h"
#include "scripting/lua-bindings/manual/network/Lua_web_socket.h"
#include "scripting/lua-bindings/manual/network/lua_http_manual.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "cocos/platform/CCNetwork.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "luasocket/socket.h"

static int tolua_Network_isLocalWiFiAvailable(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		bool tolua_ret = (bool)cocos2d::Network::isLocalWiFiAvailable();
		tolua_pushboolean(tolua_S,(bool)tolua_ret);
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'isLocalWiFiAvailable'.",&tolua_err);
	return 0;
#endif
}

static int tolua_Network_isInternetConnectionAvailable(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		bool tolua_ret = (bool)cocos2d::Network::isInternetConnectionAvailable();
		tolua_pushboolean(tolua_S,(bool)tolua_ret);
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'isInternetConnectionAvailable'.",&tolua_err);
	return 0;
#endif
}

static int tolua_Network_isHostNameReachable(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		const char* hostName = ((const char*)tolua_tostring(tolua_S,2,0));
		bool tolua_ret = (bool)cocos2d::Network::isHostNameReachable(hostName);
		tolua_pushboolean(tolua_S,(bool)tolua_ret);
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'isHostNameReachable'.",&tolua_err);
	return 0;
#endif
}

static int tolua_Network_getInternetConnectionStatus(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"Network",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		int tolua_ret = (int)cocos2d::Network::getInternetConnectionStatus();
		tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getInternetConnectionStatus'.",&tolua_err);
	return 0;
#endif
}

// new a thread to void UI blocked
static void checkIPv6Thread(lua_State *L, const char *hostname, int handler)
{
	struct addrinfo *iterator = NULL, *resolved = NULL;
	struct addrinfo hints;
	int ret = 0;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = PF_UNSPEC;
	ret = getaddrinfo(hostname, NULL, &hints, &resolved);
	if (ret != 0) {
		cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
				CCLOG("== cc.Network:isIPv6 getaddrinfo error:%d", ret);
				cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
				lua_pushinteger(L, ret);
				stack->executeFunctionByHandler(handler, 1);
				toluafix_remove_function_by_refid(L, handler);
				});
		return;
	}

	int isIpv6 = 0;
	for (iterator = resolved; iterator; iterator = iterator->ai_next) {
		char hbuf[NI_MAXHOST];
		ret = getnameinfo(iterator->ai_addr, (socklen_t) iterator->ai_addrlen,
				hbuf, (socklen_t) sizeof(hbuf), NULL, 0, NI_NUMERICHOST);
		if (ret) {
			freeaddrinfo(resolved);
			cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
					CCLOG("== cc.Network:isIPv6 getnameinfo error:%d", ret);
					cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
					lua_pushinteger(L, ret);
					stack->executeFunctionByHandler(handler, 1);
					toluafix_remove_function_by_refid(L, handler);
					});
			return;
		}
		if (iterator->ai_family == AF_INET6) {
			isIpv6 = 1;
			break;
		}
	}
	freeaddrinfo(resolved);
	cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
			cocos2d::LuaStack *stack = cocos2d::LuaEngine::getInstance()->getLuaStack();
			lua_pushnil(L);
			lua_pushboolean(L, isIpv6);
			stack->executeFunctionByHandler(handler, 2);
			toluafix_remove_function_by_refid(L, handler);
			});
}

static int tolua_Network_isIPv6(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S, 1, "Network", 0, &tolua_err) ||
			!tolua_isstring(tolua_S, 2, 0, &tolua_err) ||
			!toluafix_isfunction(tolua_S, 3, "LUA_FUNCTION", 0, &tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		const char *hostname = luaL_checkstring(tolua_S, 2);
		int handler = toluafix_ref_function(tolua_S, 3, 0);

		std::thread th(checkIPv6Thread, tolua_S, hostname, handler);
		th.detach();//exit from main thread, auto exit
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'isIPv6'.",&tolua_err);
	return 0;
#endif
}

/* Open function */
TOLUA_API int register_network_manual(lua_State* L)
{
	tolua_open(L);
	tolua_usertype(L, "Network");
	tolua_module(L, "cc", 0);
	tolua_beginmodule(L, "cc");
	tolua_cclass(L, "Network", "Network", "", NULL);
	tolua_beginmodule(L, "Network");
	tolua_function(L, "isLocalWiFiAvailable", tolua_Network_isLocalWiFiAvailable);
	tolua_function(L, "isInternetConnectionAvailable", tolua_Network_isInternetConnectionAvailable);
	tolua_function(L, "isHostNameReachable", tolua_Network_isHostNameReachable);
	tolua_function(L, "getInternetConnectionStatus", tolua_Network_getInternetConnectionStatus);
	tolua_function(L, "isIPv6", tolua_Network_isIPv6);
	tolua_endmodule(L);
	tolua_endmodule(L);

	return 1;
}

int register_network_module(lua_State* L)
{
	lua_getglobal(L, "_G");
	if (lua_istable(L,-1))//stack:...,_G,
		{
			luaopen_lua_extensions(L);
			register_web_socket_manual(L);
			register_http_manual(L);
			register_network_manual(L);
		}
	lua_pop(L, 1);

	return 1;
}
