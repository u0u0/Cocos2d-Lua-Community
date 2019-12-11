cmake_minimum_required(VERSION 3.6)

set(lib_name flatbuffers)
set(target_name ext_${lib_name})

project(${lib_name})

set(${target_name}_src
  ./flatc.cpp
  ./idl_gen_cpp.cpp
  ./idl_gen_fbs.cpp
  ./idl_gen_general.cpp
  ./idl_gen_go.cpp
  ./idl_gen_text.cpp
  ./idl_parser.cpp
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

target_compile_options(${target_name} PRIVATE "-fexceptions")
target_compile_features(${target_name} PRIVATE cxx_std_11)
target_include_directories(${target_name} PRIVATE ..)
target_include_directories(${target_name} PUBLIC .)

set_target_properties(${target_name} 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "External"
)
