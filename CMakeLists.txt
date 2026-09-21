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

set(target agloader)
if (DEFINED AGLOADER_BUILD_STATIC)
  message("Building agloader static")
  add_library(${target} STATIC)
else()
  message("Building agloader dynamic")
  add_library(${target} SHARED)
  target_compile_definitions(agloader PUBLIC COMPILE_DYNAMIC)
endif()

get_target_property(IS_IMPORTED ${target} IMPORTED)
message("Is ${target} imported: ${IS_IMPORTED}")

if (NOT IS_IMPORTED)
  message("Adding tests for ${target}")
  add_subdirectory(tests)
endif()

set_my_standards_cxx_options(agloader 23)

if(MSVC)
  set(driver_file msvc)
else()
  set(driver_file linux)
endif()

target_sources(${target}
PUBLIC
  FILE_SET HEADERS
  FILES
    src/loader_export.hpp
)

target_sources(${target}
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

target_include_directories(${target} PUBLIC src)
target_link_libraries(${target} PRIVATE ${CMAKE_DL_LIBS})
build_docs_standard(${target}_docs)

message(STATUS "agloader ver.  ${PROJECT_VERSION}")