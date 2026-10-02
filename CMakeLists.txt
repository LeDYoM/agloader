cmake_minimum_required(VERSION 4.0)
project(
  "AGLoader"
  VERSION 0.4.1.4
  DESCRIPTION "Multiplatform library to load shared libraries system agnostic"
  HOMEPAGE_URL https://github.com/LeDYoM/agloader
  LANGUAGES CXX)

# Start common part to get CMake common scripts
include(FetchContent)

# Fetch my cmake utils package
FetchContent_Declare(
  cmake_ledyom_utils
  GIT_REPOSITORY https://github.com/LeDYoM/cmake_ledyom_utils.git
)

FetchContent_MakeAvailable(cmake_ledyom_utils)
list(APPEND CMAKE_MODULE_PATH ${cmake_ledyom_utils_SOURCE_DIR})

include(c_l_u_a)
# Finish common part

prepare_cmake_presets()

set(target agloader)

add_library(${target} SHARED)
target_compile_definitions(agloader PUBLIC COMPILE_DYNAMIC)

option(AGLOADER_BUILD_TESTS "Build test programs" ON)

message("Is ${target} imported: ${PROJECT_IS_TOP_LEVEL}")
message("Building tests: ${AGLOADER_BUILD_TESTS}")

if (${AGLOADER_BUILD_TESTS})
  message("Adding tests for ${target}")
  add_subdirectory(tests)
else()
  message("Not building tests for ${target}")
endif()

set_my_standards_cxx_options(${target} 23)

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
build_docs_standard(${target})

message(STATUS "agloader ver.  ${PROJECT_VERSION}")
