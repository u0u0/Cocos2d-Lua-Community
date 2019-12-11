cmake_minimum_required(VERSION 3.6)

set(lib_name cpufeatures)
set(target_name ext_${lib_name})

project(lib_name)

# CMake from android SDK set ANDROID_NDK instead of CMAKE_ANDROID_NDK
if(ANDROID_NDK)
    add_library(${target_name} ${ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c)
    target_include_directories(${target_name} PUBLIC ${ANDROID_NDK}/sources/android/cpufeatures)
else()
    add_library(${target_name} ${CMAKE_ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c)
    target_include_directories(${target_name} PUBLIC ${CMAKE_ANDROID_NDK}/sources/android/cpufeatures)
endif()

target_link_libraries(${target_name} dl)
