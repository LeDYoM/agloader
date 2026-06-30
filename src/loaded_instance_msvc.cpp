export module agloader:pfunctions;

#if defined(_MSC_VER) || defined(__BORLANDC__)
#define WIN32_LEAN_AND_MEAN
import <windows.h>;
#undef WIN32_LEAN_AND_MEAN

void* getMethod(void* handle, const char* methodName)
{
    return static_cast<void*>(
        GetProcAddress(static_cast<HMODULE>(handle), methodName));
}

void* loadSharedObject(const char* fileName)
{
    return static_cast<void*>(LoadLibrary(fileName));
}

bool freeSharedObject(void* handle)
{
    return (FreeLibrary(static_cast<HMODULE>(handle)) != 0);
}

constexpr char const extension[] = ".dll";
constexpr char const prefix[]    = "";

#endif
