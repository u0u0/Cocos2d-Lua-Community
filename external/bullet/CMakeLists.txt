cmake_minimum_required(VERSION 3.6)

set(lib_name bullet)
set(target_name ext_${lib_name})

project(${lib_name})

include(../cmake/CocosExternalConfig.cmake)

add_library(${target_name} STATIC IMPORTED GLOBAL)

set_property(TARGET ${target_name} APPEND PROPERTY
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
set_property(TARGET ${target_name} APPEND PROPERTY
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/bullet"
)

if(WINDOWS)
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION_DEBUG "${platform_spec_path}/debug/lib${lib_name}.lib"
    IMPORTED_LOCATION_RELEASE "${platform_spec_path}/release/lib${lib_name}.lib"
  )
  set_target_properties(${target_name} PROPERTIES
    MAP_IMPORTED_CONFIG_MINSIZEREL Release
    MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release
  )
else()
  set_target_properties(${target_name} PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/libLinearMath.a"
  )

  # multi libs
  add_library(bulletcollision STATIC IMPORTED)
  set_target_properties(bulletcollision PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/libBulletCollision.a"
  )
  add_library(bulletdynamics STATIC IMPORTED)
  set_target_properties(bulletdynamics PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/libBulletDynamics.a"
  )
  add_library(bulletmultithreaded STATIC IMPORTED)
  set_target_properties(bulletmultithreaded PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/libBulletMultiThreaded.a"
  )
  add_library(minicl STATIC IMPORTED)
  set_target_properties(minicl PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/libMiniCL.a"
  )
  add_library(linearmath STATIC IMPORTED)
  set_target_properties(linearmath PROPERTIES
    IMPORTED_LOCATION "${platform_spec_path}/libLinearMath.a"
  )

  # internal link depend
  set_property(TARGET bulletcollision APPEND PROPERTY INTERFACE_LINK_LIBRARIES "linearmath")
  set_property(TARGET bulletdynamics APPEND PROPERTY INTERFACE_LINK_LIBRARIES "bulletcollision")

  # mark multi libs link into single one: "${target_name}"
  set_property(TARGET ${target_name} APPEND PROPERTY
    INTERFACE_LINK_LIBRARIES "bulletcollision"
  )
  set_property(TARGET ${target_name} APPEND PROPERTY
    INTERFACE_LINK_LIBRARIES "bulletdynamics"
  )
  set_property(TARGET ${target_name} APPEND PROPERTY
    INTERFACE_LINK_LIBRARIES "bulletmultithreaded"
  )
  set_property(TARGET ${target_name} APPEND PROPERTY
    INTERFACE_LINK_LIBRARIES "minicl"
  )
endif()


