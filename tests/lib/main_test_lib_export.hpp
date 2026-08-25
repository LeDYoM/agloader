#ifndef LOADER_TEST_LIB_EXPORT_INCLUDE_HPP
#define LOADER_TEST_LIB_EXPORT_INCLUDE_HPP

#ifdef _WIN32
    #define LOADER_TEST_API __declspec(dllexport)
    #define LOADER_TEST_PRIVATE
#else
    #define LOADER_TEST_API __attribute__((visibility("default")))
    #define LOADER_TEST_PRIVATE __attribute__((visibility("hidden")))
#endif

#endif
