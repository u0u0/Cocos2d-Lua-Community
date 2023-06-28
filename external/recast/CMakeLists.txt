cmake_minimum_required(VERSION 3.6)

set(lib_name recast)
set(target_name ext_${lib_name})

project(${lib_name})

set(${target_name}_src
  DebugUtils/DebugDraw.cpp
  DebugUtils/DetourDebugDraw.cpp
  Detour/DetourAlloc.cpp
  Detour/DetourCommon.cpp
  Detour/DetourNavMesh.cpp
  Detour/DetourNavMeshBuilder.cpp
  Detour/DetourNavMeshQuery.cpp
  Detour/DetourNode.cpp
  DetourCrowd/DetourCrowd.cpp
  DetourCrowd/DetourLocalBoundary.cpp
  DetourCrowd/DetourObstacleAvoidance.cpp
  DetourCrowd/DetourPathCorridor.cpp
  DetourCrowd/DetourPathQueue.cpp
  DetourCrowd/DetourProximityGrid.cpp
  DetourTileCache/DetourTileCache.cpp
  DetourTileCache/DetourTileCacheBuilder.cpp
  fastlz/fastlz.c
)

add_library(${target_name} STATIC
  ${${target_name}_src}
)

target_include_directories(${target_name} PUBLIC ..)

set_target_properties(${target_name}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    FOLDER "External"
)
