cmake_minimum_required(VERSION 3.6)

set(lib_name fmod)
set(target_name ext_${lib_name})

project(${lib_name})

add_library(${target_name} SHARED IMPORTED GLOBAL)

set_target_properties(${target_name} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/prebuilt/64-bit/lib${lib_name}.so"
)

