#ifdef LINUX
module;

// For now, windows or linux
#include <dlfcn.h>

export module agloader:os_specific_functions;

[[nodiscard]] void* getMethod(void* handle,
                              char const* const methodName) noexcept
{
    return static_cast<void*>(dlsym(handle, methodName));
}

[[nodiscard]] void* loadSharedObject(char const* const fileName) noexcept
{
    return static_cast<void*>(dlopen(fileName, RTLD_LAZY));
}

bool freeSharedObject(void* handle) noexcept
{
    return (dlclose(handle) == 0);
}

constexpr char const extension[] = ".so";
constexpr char const prefix[]    = "./lib";

#endif
