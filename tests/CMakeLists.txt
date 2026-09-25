cmake_minimum_required (VERSION 4.0)
project(agloader_utests CXX)

set(target agloader_utests)
set(auxiliary_target agloader_test_lib)

add_executable(agloader_utests)
add_library(agloader_test_lib SHARED)

target_sources(agloader_utests PRIVATE
    src/main.cpp)

target_sources(agloader_test_lib PRIVATE
    lib/main_test_lib_export.hpp
    lib/main_test_lib.cpp)

set_my_standards_cxx_options("agloader_utests;agloader_test_lib" 23)

target_link_libraries(agloader_utests PRIVATE agloader)
add_test(NAME agloader_utests COMMAND agloader_utests)

add_custom_command(TARGET agloader_utests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:agloader>
        $<TARGET_FILE_DIR:agloader_utests>)
