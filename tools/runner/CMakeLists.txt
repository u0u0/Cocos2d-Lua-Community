# Lua Game Runner, a desktop app to debug Lua.

cmake_minimum_required(VERSION 3.10)

set(APP_NAME LuaGameRunner)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
set(BUILD_LUA_LIBS ON)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers
set(GAME_HEADER
   	${CMAKE_CURRENT_SOURCE_DIR}/Classes/AppDelegate.h
   	${CMAKE_CURRENT_SOURCE_DIR}/Classes/setup.h
	)
set(GAME_SOURCE
   	${CMAKE_CURRENT_SOURCE_DIR}/Classes/AppDelegate.cpp
   	${CMAKE_CURRENT_SOURCE_DIR}/Classes/setup.cpp
	)
# sources need to compile info, include dirs and source files

if(LINUX)
	list(APPEND GAME_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/proj.linux/main.cpp)
elseif(WINDOWS)
	list(APPEND GAME_HEADER
		${CMAKE_CURRENT_SOURCE_DIR}/proj.win32/getopt.h
		${CMAKE_CURRENT_SOURCE_DIR}/proj.win32/main.h
		${CMAKE_CURRENT_SOURCE_DIR}/proj.win32/resource.h
		)
	list(APPEND GAME_SOURCE
		${CMAKE_CURRENT_SOURCE_DIR}/proj.win32/getopt.c
		${CMAKE_CURRENT_SOURCE_DIR}/proj.win32/main.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/proj.win32/game.rc
		)
elseif(MACOSX)
	list(APPEND GAME_HEADER
		${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/ConsoleWindowController.h
		)
	set(APP_UI_RES
		${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Icon.icns
		${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/ConsoleWindow.xib
		)
	list(APPEND GAME_SOURCE
		${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/main.mm
		${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Prefix.pch
		${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/ConsoleWindowController.m
		${APP_UI_RES}
		)
endif()

set(APP_SRC ${GAME_HEADER} ${GAME_SOURCE})

# mark app complie info and libs info
add_executable(${APP_NAME} ${APP_SRC})
target_link_libraries(${APP_NAME} luacocos2d)
target_include_directories(${APP_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Classes)

# mark app resources, resource will be copy auto after mark
setup_cocos_app_config(${APP_NAME})
# always open COCOS2D_DEBUG in cocos2d
target_compile_definitions(cocos2d PUBLIC $<$<CONFIG:Release>:COCOS2D_DEBUG=1>)
if(MACOSX)
	set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
	set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
	set_xcode_property(${APP_NAME} INSTALL_PATH "\${LOCAL_APPS_DIR}") # fix archive no file
	set_xcode_property(${APP_NAME} OTHER_LDFLAGS[arch=x86_64] "-pagezero_size 10000 -image_base 100000000 $(inherited)")
	set_target_properties(${APP_NAME} PROPERTIES
		MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.mac/Info.plist"
		)
elseif(WINDOWS)
	cocos_copy_target_dll(${APP_NAME})
endif()

