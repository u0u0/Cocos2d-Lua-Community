cmake_minimum_required(VERSION 3.6)

set(lib_name OpenAL)
set(target_name ext_${lib_name})
project(${lib_name})

include(../cmake/CocosExternalConfig.cmake)

if(WINDOWS)
  add_library(${target_name} SHARED IMPORTED GLOBAL)
else()
  add_library(${target_name} STATIC IMPORTED GLOBAL)
endif()

set_target_properties(${target_name} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
if(WINDOWS)
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/OpenAL32.dll"
    IMPORTED_IMPLIB "${platform_spec_path}/common.lib"
    IMPORTED_IMPLIB "${platform_spec_path}/OpenAL32.lib"
  )
else()
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/libcommon.a"
    IMPORTED_LOCATION "${platform_spec_path}/libopenal.a"
  )
endif()
