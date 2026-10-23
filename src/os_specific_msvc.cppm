export module agloader:os_specific_functions;

#if defined(_MSC_VER) || defined(__BORLANDC__)
#define WIN32_LEAN_AND_MEAN
import <windows.h>;
#undef WIN32_LEAN_AND_MEAN

[[nodiscard]] void* getMethod(void* handle, char const* methodName) noexcept
{
    return static_cast<void*>(
        GetProcAddress(static_cast<HMODULE>(handle), methodName));
}

[[nodiscard]] void* loadSharedObject(char const* fileName) noexcept
{
    return static_cast<void*>(LoadLibrary(fileName));
}

bool freeSharedObject(void* handle) noexcept
{
    return (FreeLibrary(static_cast<HMODULE>(handle)) != 0);
}

constexpr char const extension[] = ".dll";
constexpr char const prefix[]    = "";

#endif
