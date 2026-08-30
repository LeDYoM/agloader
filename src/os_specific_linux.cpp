#ifdef LINUX
module;

// For now, windows or linux
#include <dlfcn.h>

export module agloader:os_specific_functions;

void* getMethod(void* handle, char const* const methodName)
{
    return static_cast<void*>(dlsym(handle, methodName));
}

void* loadSharedObject(char const* const fileName)
{
    return static_cast<void*>(dlopen(fileName, RTLD_LAZY));
}

bool freeSharedObject(void* handle)
{
    return (dlclose(handle) == 0);
}

constexpr char const extension[] = ".so";
constexpr char const prefix[]    = "./lib";

#endif
