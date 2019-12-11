cmake_minimum_required(VERSION 3.6)

set(lib_name luasocket)
set(target_name ext_${lib_name})

project(${lib_name})

set(${target_name}_src
  buffer.c
  io.c
  timeout.c
  select.c
  udp.c
  mime.c
  tcp.c
  auxiliar.c
  inet.c
  luasocket.c
  luasocket_scripts.c
  except.c
  options.c
)

if(WINDOWS)
  list(APPEND ${target_name}_src 
    wsocket.c
  )
else()
  list(APPEND ${target_name}_src 
    unix.c
    usocket.c
    serial.c
  )
endif()


add_library(${target_name} STATIC
  ${${target_name}_src}
)

if(LINUX)
  target_compile_definitions(${target_name} PRIVATE _GNU_SOURCE)
endif()

target_include_directories(${target_name} 
  INTERFACE ..
  PRIVATE ../luajit/include
)

set_target_properties(${target_name}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "External"
)

# TODO CHECK "lua/prebuilt/ios/liblua.a" IS NECESSARY?
