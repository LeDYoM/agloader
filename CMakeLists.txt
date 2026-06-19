cmake_minimum_required(VERSION 3.14)
project(
  "AGLoader"
  VERSION 0.3.1.1
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  HOMEPAGE_URL https://github.com/LeDYoM/agloader
  LANGUAGES CXX)

set(CURRENT_TARGET agloader)
set(AGLOADER_BUILD_STATIC TRUE)

if (DEFINED AGLOADER_BUILD_STATIC)
  message("Building agloader static")
  add_library(${CURRENT_TARGET} STATIC)
else()
  message("Building agloader dynamic")
  add_library(${CURRENT_TARGET} SHARED)
endif()

set_target_properties(${CURRENT_TARGET} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON)

target_compile_options(${CURRENT_TARGET} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Wall>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unknown-pragmas>
)

target_compile_options(${CURRENT_TARGET} PRIVATE -fsanitize=address)
target_link_options(${CURRENT_TARGET} PRIVATE -fsanitize=address)

set_property(TARGET ${CURRENT_TARGET} PROPERTY COMPILE_WARNING_AS_ERROR ON)

if(MSVC)
  set(driver_file msvc)
else()
  set(driver_file linux)
endif()

target_sources(${CURRENT_TARGET}
PUBLIC
  FILE_SET HEADERS
  FILES
    src/loader_export.hpp
)

target_sources(${CURRENT_TARGET}
PUBLIC
  FILE_SET CXX_MODULES
  FILES
    src/agloader.ixx
    src/loaded_instance_${driver_file}.cpp
    src/loaded_instance_utils.cpp
    src/loaded_instance.cpp
    src/loader_impl.cpp
    src/loader_management_impl.cpp
    src/loader_management.cpp
    src/loader.cpp
)

target_link_libraries(${CURRENT_TARGET} PRIVATE ${CMAKE_DL_LIBS})
