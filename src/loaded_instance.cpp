export module agloader:linstance;

import <map>;
import <string>;
import <cstring>;

import :os_specific_functions;

namespace agl
{
class LoadedInstance
{
public:
    LoadedInstance() = default;

    ~LoadedInstance() { unload(); }

    bool load(char const* const fileName)
    {
        // A bit of old C code.
        static constexpr auto kBufferSize{1024};
        static char strBuffer[kBufferSize];
        strBuffer[0] = 0;

        strcpy_s(strBuffer, kBufferSize, prefix);
        strcat_s(strBuffer, kBufferSize, fileName);
        strcat_s(strBuffer, kBufferSize, extension);

        m_shared_file_handle = loadSharedObject(strBuffer);
        return loaded();
    }

    void const* loadMethod(char const* const methodName)
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

    bool loaded() const { return m_shared_file_handle != nullptr; }

    bool unload()
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

    void const* loadedData() const { return m_shared_file_handle; }

private:
    void* m_shared_file_handle{nullptr};
    std::map<std::string, void*> m_methods;
};
}  // namespace agl
