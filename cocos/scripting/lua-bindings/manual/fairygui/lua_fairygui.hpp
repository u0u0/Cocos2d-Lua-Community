#include "base/ccConfig.h"
#ifndef __lua_fairygui_h__
#define __lua_fairygui_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_fairygui_manual(lua_State* tolua_S);

#endif // __lua_fairygui_h__
