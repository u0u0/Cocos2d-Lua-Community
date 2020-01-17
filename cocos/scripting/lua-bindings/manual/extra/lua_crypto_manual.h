#ifndef __LUA_CRYPTO_MANUAL_H_
#define __LUA_CRYPTO_MANUAL_H_

extern "C" {
#include "lua.h"
#include "tolua++.h"
}
#include "scripting/lua-bindings/manual/tolua_fix.h"

TOLUA_API int register_crypto_module(lua_State* tolua_S);

#endif // __LUA_CRYPTO_MANUAL_H_
