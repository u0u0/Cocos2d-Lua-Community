cmake_minimum_required(VERSION 3.6)

set(lib_name libvorbis)
set(target_name ext_${lib_name})

project(${lib_name})

set(${target_name}_src
  lib/analysis.c
  lib/bitrate.c
  lib/block.c
  lib/codebook.c
  lib/envelope.c
  lib/floor0.c
  lib/floor1.c
  lib/info.c
  lib/lookup.c
  lib/lpc.c
  lib/lsp.c
  lib/mapping0.c
  lib/mdct.c
  lib/psy.c
  lib/registry.c
  lib/res0.c
  lib/sharedbook.c
  lib/smallft.c
  lib/synthesis.c
  lib/vorbisenc.c
  lib/vorbisfile.c
  lib/window.c
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

target_include_directories(${target_name}
  PUBLIC .
  PUBLIC ./lib
  PUBLIC ../libogg
)

if(ANDROID)
	if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv7-a -mfloat-abi=softfp")
	endif()
endif()

set_target_properties(${target_name}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "External"
)

