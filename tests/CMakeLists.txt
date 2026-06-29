cmake_minimum_required (VERSION 4.0)
project(agloader_utests CXX)

add_executable(agloader_utests)

target_sources(agloader_utests PRIVATE
    init.tests.cpp
    main.cpp)

target_compile_options(agloader_utests PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/Wall>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Wno-unknown-pragmas>
)

target_link_libraries(agloader_utests PRIVATE agloader)
add_test(NAME agloader_utests COMMAND agloader_utests)
