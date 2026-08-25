cmake_minimum_required (VERSION 4.0)
project(agloader_utests CXX)

add_executable(agloader_utests)
add_library(agloader_test_lib SHARED)

target_sources(agloader_utests PRIVATE
    src/main.cpp)

target_sources(agloader_test_lib PRIVATE
    lib/main_test_lib_export.hpp
    lib/main_test_lib.cpp)

target_compile_options(agloader_utests PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Wall>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unknown-pragmas>
)

target_compile_options(agloader_test_lib PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Wall>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unknown-pragmas>
)

set_target_properties(agloader_utests agloader_test_lib PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON)

set_property(TARGET agloader_utests PROPERTY COMPILE_WARNING_AS_ERROR ON)
set_property(TARGET agloader_test_lib PROPERTY COMPILE_WARNING_AS_ERROR ON)

set_target_properties(agloader_utests agloader_test_lib PROPERTIES CXX_STANDARD 23)

target_link_libraries(agloader_utests PRIVATE agloader)
add_test(NAME agloader_utests COMMAND agloader_utests)

add_custom_command(TARGET agloader_utests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:agloader>
        $<TARGET_FILE_DIR:agloader_utests>)