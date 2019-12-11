cmake_minimum_required(VERSION 3.6)

set(lib_name chipmunk)
set(target_name ext_${lib_name})

project(${lib_name})

include(../cmake/CocosExternalConfig.cmake)

add_library(${target_name} STATIC IMPORTED GLOBAL)

set_target_properties(${target_name} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
if(WINDOWS)
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION_DEBUG "${platform_spec_path}/debug-lib/lib${lib_name}.lib"
    IMPORTED_LOCATION_RELEASE "${platform_spec_path}/release-lib/lib${lib_name}.lib"
  )
  set_target_properties(${target_name} PROPERTIES
    MAP_IMPORTED_CONFIG_MINSIZEREL Release
    MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )
else()
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/lib${lib_name}.a"
  )
endif()
