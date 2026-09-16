cmake_minimum_required(VERSION 4.0)
project(
  "AGLoader"
  VERSION 0.4.0.0
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  HOMEPAGE_URL https://github.com/LeDYoM/agloader
  LANGUAGES CXX)

#set(AGLOADER_BUILD_STATIC TRUE)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_ledyom_utils" ${CMAKE_MODULE_PATH})
include(documenting)
include(compiling)

if (DEFINED AGLOADER_BUILD_STATIC)
  message("Building agloader static")
  add_library(agloader STATIC)
else()
  message("Building agloader dynamic")
  add_library(agloader SHARED)
  target_compile_definitions(agloader PUBLIC COMPILE_DYNAMIC)
endif()

get_target_property(IS_IMPORTED agloader IMPORTED)
message("Is agloader imported: ${IS_IMPORTED}")

if (NOT IS_IMPORTED)
  message("Adding tests for agloader")
  add_subdirectory(tests)
endif()

set_cxx_standard(agloader 23)
add_pie_if_available(agloader)
target_compile_options(agloader PRIVATE
  $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<NOT:$<CONFIG:Release>>>:/Wall>
  $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unknown-pragmas>
)

# Avoid warnings from external includes (like STL, for example)
target_compile_options(agloader PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/external:anglebrackets /external:W0>
)

set_property(TARGET agloader PROPERTY COMPILE_WARNING_AS_ERROR ON)

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
    src/public/agloader.ixx
    src/public/imodule.cppm
    src/public/loader_management.cppm
    src/loaded_instance.cppm
    src/loader.cppm
    src/module.cppm
    src/os_specific_${driver_file}.cppm
)

target_include_directories(agloader PUBLIC src)
target_link_libraries(agloader PRIVATE ${CMAKE_DL_LIBS})
message(STATUS "agloader ver.  ${PROJECT_VERSION}")
build_docs(agloader)