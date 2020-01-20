#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/network/CCHTTPRequest.h"

using namespace cocos2d;

static int tolua_HTTPRequest_createWithUrl(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertable(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			(tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
			!tolua_isstring(tolua_S,3,0,&tolua_err) ||
			!tolua_isnumber(tolua_S,4,1,&tolua_err) ||
			!tolua_isnoobj(tolua_S,5,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		LUA_FUNCTION listener = (  toluafix_ref_function(tolua_S,2,0));
		const char* url = ((const char*)  tolua_tostring(tolua_S,3,0));
		int method = ((int)  tolua_tonumber(tolua_S,4,kCCHTTPRequestMethodGET));
		{
			HTTPRequest* tolua_ret = (HTTPRequest*)  HTTPRequest::createWithUrlLua(listener,url,method);
			tolua_pushusertype(tolua_S,(void*)tolua_ret,"HTTPRequest");
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'createWithUrl'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_setRequestUrl(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		const char* url = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRequestUrl'", NULL);
#endif
		{
			self->setRequestUrl(url);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'setRequestUrl'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getRequestUrl(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRequestUrl'", NULL);
#endif
		{
			string tolua_ret = (string)  self->getRequestUrl();
			tolua_pushcppstring(tolua_S, tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getRequestUrl'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_addRequestHeader(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		const char* header = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addRequestHeader'", NULL);
#endif
		{
			self->addRequestHeader(header);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'addRequestHeader'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_addPOSTValue(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isstring(tolua_S,3,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,4,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
		const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addPOSTValue'", NULL);
#endif
		{
			self->addPOSTValue(key,value);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'addPOSTValue'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_setPOSTData(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		const char* data = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPOSTData'", NULL);
#endif
		{
			size_t len;
			lua_tolstring(tolua_S, 2, &len);
			self->setPOSTData(data, len);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'setPOSTData'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_addFormFile(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isstring(tolua_S,3,0,&tolua_err) ||
			!tolua_isstring(tolua_S,4,1,&tolua_err) ||
			!tolua_isnoobj(tolua_S,5,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
		const char* filePath = ((const char*)  tolua_tostring(tolua_S,3,0));
		const char* fileType = ((const char*)  tolua_tostring(tolua_S,4,"application/octet-stream"));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addFormFile'", NULL);
#endif
		{
			self->addFormFile(name,filePath,fileType);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'addFormFile'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_addFormContents(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isstring(tolua_S,3,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,4,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
		const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addFormContents'", NULL);
#endif
		{
			self->addFormContents(name,value);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'addFormContents'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_setCookieString(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		const char* cookie = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCookieString'", NULL);
#endif
		{
			self->setCookieString(cookie);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'setCookieString'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getCookieString(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCookieString'", NULL);
#endif
		{
			string tolua_ret = (string)  self->getCookieString();
			tolua_pushcppstring(tolua_S, tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getCookieString'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_setAcceptEncoding(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		int acceptEncoding = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAcceptEncoding'", NULL);
#endif
		{
			self->setAcceptEncoding(acceptEncoding);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'setAcceptEncoding'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_setTimeout(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnumber(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		int timeout = ((int)  tolua_tonumber(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTimeout'", NULL);
#endif
		{
			self->setTimeout(timeout);
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'setTimeout'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_start(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'start'", NULL);
#endif
		{
			bool tolua_ret = (bool)  self->start();
			tolua_pushboolean(tolua_S,(bool)tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'start'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_cancel(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancel'", NULL);
#endif
		{
			self->cancel();
		}
	}
	return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'cancel'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getState(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getState'", NULL);
#endif
		{
			int tolua_ret = (int)  self->getState();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getState'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getResponseStatusCode(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseStatusCode'", NULL);
#endif
		{
			int tolua_ret = (int)  self->getResponseStatusCode();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getResponseStatusCode'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getResponseHeadersString(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseHeadersString'", NULL);
#endif
		{
			string tolua_ret = (string)  self->getResponseHeadersString();
			tolua_pushcppstring(tolua_S, tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getResponseHeadersString'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getResponseString(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseString'", NULL);
#endif
		{
			string tolua_ret = (string)  self->getResponseString();
			tolua_pushcppstring(tolua_S, tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getResponseString'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getResponseData(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseDataLua'", NULL);
#endif
		{
			self->getResponseDataLua();

		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getResponseData'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getResponseDataLength(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getResponseDataLength'", NULL);
#endif
		{
			int tolua_ret = (int)  self->getResponseDataLength();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getResponseDataLength'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_saveResponseData(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isstring(tolua_S,2,0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,3,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
		const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'saveResponseData'", NULL);
#endif
		{
			int tolua_ret = (int)  self->saveResponseData(filename);
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'saveResponseData'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getErrorCode(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getErrorCode'", NULL);
#endif
		{
			int tolua_ret = (int)  self->getErrorCode();
			tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getErrorCode'.",&tolua_err);
	return 0;
#endif
}

static int tolua_HTTPRequest_getErrorMessage(lua_State* tolua_S)
{
#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
	if (
			!tolua_isusertype(tolua_S,1,"HTTPRequest",0,&tolua_err) ||
			!tolua_isnoobj(tolua_S,2,&tolua_err)
	   )
		goto tolua_lerror;
	else
#endif
	{
		HTTPRequest* self = (HTTPRequest*)  tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getErrorMessage'", NULL);
#endif
		{
			string tolua_ret = (string)  self->getErrorMessage();
			tolua_pushcppstring(tolua_S, tolua_ret);
		}
	}
	return 1;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'getErrorMessage'.",&tolua_err);
	return 0;
#endif
}

/* Open function */
TOLUA_API int register_http_manual(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	tolua_usertype(tolua_S, "HTTPRequest");
	tolua_module(tolua_S, "cc", 0);
	tolua_beginmodule(tolua_S, "cc");
	tolua_cclass(tolua_S, "HTTPRequest", "HTTPRequest", "cc.Ref", NULL);
	tolua_beginmodule(tolua_S, "HTTPRequest");
	tolua_function(tolua_S, "createWithUrl", tolua_HTTPRequest_createWithUrl);
	tolua_function(tolua_S, "setRequestUrl", tolua_HTTPRequest_setRequestUrl);
	tolua_function(tolua_S, "getRequestUrl", tolua_HTTPRequest_getRequestUrl);
	tolua_function(tolua_S, "addRequestHeader", tolua_HTTPRequest_addRequestHeader);
	tolua_function(tolua_S, "addPOSTValue", tolua_HTTPRequest_addPOSTValue);
	tolua_function(tolua_S, "setPOSTData", tolua_HTTPRequest_setPOSTData);
	tolua_function(tolua_S, "addFormFile", tolua_HTTPRequest_addFormFile);
	tolua_function(tolua_S, "addFormContents", tolua_HTTPRequest_addFormContents);
	tolua_function(tolua_S, "setCookieString", tolua_HTTPRequest_setCookieString);
	tolua_function(tolua_S, "getCookieString", tolua_HTTPRequest_getCookieString);
	tolua_function(tolua_S, "setAcceptEncoding", tolua_HTTPRequest_setAcceptEncoding);
	tolua_function(tolua_S, "setTimeout", tolua_HTTPRequest_setTimeout);
	tolua_function(tolua_S, "start", tolua_HTTPRequest_start);
	tolua_function(tolua_S, "cancel", tolua_HTTPRequest_cancel);
	tolua_function(tolua_S, "getState", tolua_HTTPRequest_getState);
	tolua_function(tolua_S, "getResponseStatusCode", tolua_HTTPRequest_getResponseStatusCode);
	tolua_function(tolua_S, "getResponseHeadersString", tolua_HTTPRequest_getResponseHeadersString);
	tolua_function(tolua_S, "getResponseString", tolua_HTTPRequest_getResponseString);
	tolua_function(tolua_S, "getResponseData", tolua_HTTPRequest_getResponseData);
	tolua_function(tolua_S, "getResponseDataLength", tolua_HTTPRequest_getResponseDataLength);
	tolua_function(tolua_S, "saveResponseData", tolua_HTTPRequest_saveResponseData);
	tolua_function(tolua_S, "getErrorCode", tolua_HTTPRequest_getErrorCode);
	tolua_function(tolua_S, "getErrorMessage", tolua_HTTPRequest_getErrorMessage);
	tolua_endmodule(tolua_S);
	tolua_endmodule(tolua_S);
    
	return 1;
}
