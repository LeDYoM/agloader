cmake_minimum_required(VERSION 4.0)
project(
  "AGLoader"
  VERSION 0.3.1.6
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  HOMEPAGE_URL https://github.com/LeDYoM/agloader
  LANGUAGES CXX)

set(AGLOADER_BUILD_STATIC TRUE)

if (DEFINED AGLOADER_BUILD_STATIC)
  message("Building agloader static")
  add_library(agloader STATIC)
else()
  message("Building agloader dynamic")
  add_library(agloader SHARED)
endif()

get_target_property(IS_IMPORTED agloader IMPORTED)
message("Is agloader imported: ${IS_IMPORTED}")

if (NOT IS_IMPORTED)
  message("Adding tests for agloader")
  add_subdirectory(tests)
endif()

set_target_properties(agloader agloader_utests PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON)

target_compile_options(agloader PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/external:anglebrackets /external:W0>
)

target_compile_options(agloader PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Wall>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unknown-pragmas>
)

set_property(TARGET agloader agloader_utests PROPERTY COMPILE_WARNING_AS_ERROR ON)

if(MSVC)
  set(driver_file msvc)
else()
  set(driver_file linux)
endif()

target_sources(agloader
PUBLIC
  FILE_SET HEADERS
  FILES
    src/loader_export.hpp
)

target_sources(agloader
PUBLIC
  FILE_SET CXX_MODULES
  FILES
    src/agloader.ixx
    src/loaded_instance_impl.cpp
    src/loaded_instance_${driver_file}.cpp
    src/loaded_instance_utils.cpp
    src/loaded_instance.cpp
    src/loader_impl.cpp
    src/loader_management_impl.cpp
    src/loader_management.cpp
    src/loader.cpp
)

target_link_libraries(agloader PRIVATE ${CMAKE_DL_LIBS})
message(STATUS "agloader ver.  ${CMAKE_PROJECT_VERSION}")
