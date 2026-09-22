cmake_minimum_required(VERSION 4.0)
project(
  "AGLoader"
  VERSION 0.4.1.1
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  HOMEPAGE_URL https://github.com/LeDYoM/agloader
  LANGUAGES CXX)

# Start common part to get CMake common scripts
include(FetchContent)

# Fetch my cmake utils package
FetchContent_Declare(
  cmake_ledyom_utils
  GIT_REPOSITORY https://github.com/LeDYoM/cmake_ledyom_utils.git
  GIT_TAG agloader_code
)

FetchContent_MakeAvailable(cmake_ledyom_utils)
set(CMAKE_MODULE_PATH "${cmake_ledyom_utils_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

include(documenting)
include(compiling)
# Finish common part

#set(AGLOADER_BUILD_STATIC TRUE)
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