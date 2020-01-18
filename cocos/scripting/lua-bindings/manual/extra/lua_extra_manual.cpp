#include "scripting/lua-bindings/manual/extra/lua_extra_manual.h"
#include "scripting/lua-bindings/manual/extra/lua_crypto_manual.h"

TOLUA_API int register_extra_manual_all(lua_State* tolua_S)
{
    register_crypto_module(tolua_S);
    return 1;
}
