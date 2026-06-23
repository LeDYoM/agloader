module;

#include <map>
#include <string>

module agloader;

import :pfunctions;
import :utils;

namespace agl
{
LoadedInstance::LoadedInstance()  = default;
LoadedInstance::~LoadedInstance() = default;

bool LoadedInstance::load(const char* fileName)
{
    m_shared_file_handle =
        loadSharedObject(formatFileName(fileName, extension, prefix).c_str());
    return loaded();
}

void const* LoadedInstance::loadMethod(const char* methodName)
{
    if (loaded())
    {
        auto node{m_methods.find(methodName)};
        if (node == m_methods.end())
        {
            auto methodAddress{getMethod(m_shared_file_handle, methodName)};

            // Add the result of getMethod even if is nullptr to avoid
            // trying to load it more times
            m_methods[methodName] = methodAddress;
            return methodAddress;
        }
        else
        {
            // The method is already on the map, return it
            return node->second;
        }
    }
    return nullptr;
}

bool LoadedInstance::loaded() const
{
    return m_shared_file_handle != nullptr;
}

bool LoadedInstance::unload()
{
    bool result{false};

    if (loaded())
    {
        result = freeSharedObject(m_shared_file_handle);
    }
    m_shared_file_handle = nullptr;
    m_methods.clear();
    return result;
}

void const* LoadedInstance::loadedData() const
{
    return m_shared_file_handle;
}

}  // namespace agl
