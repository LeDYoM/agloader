/**
 * @file loader_export.hpp
 * @brief API definitions
 * This macros define the visibilty of the public and private calls for the
 * agloader library
 * @def LOADER_API Defines the call convention for Loader API calls
 * @def LOADER_PRIVATE Defines the call convention for Loader private functions
*/
#ifndef LOADER_EXPORT_INCLUDE_HPP
#define LOADER_EXPORT_INCLUDE_HPP

/**
 */
#ifdef COMPILE_DYNAMIC
#ifdef _WIN32
#define LOADER_API __declspec(dllexport)
#define LOADER_PRIVATE
#else
#define LOADER_API __attribute__((visibility("default")))
#define LOADER_PRIVATE __attribute__((visibility("hidden")))
#endif
#else
#define LOADER_API
#define LOADER_PRIVATE
#endif

#endif
