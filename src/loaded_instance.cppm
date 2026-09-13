export module agloader:linstance;

import <map>;
import <string>;
import <cstring>;

import :os_specific_functions;

namespace agl
{
/**
 * @brief This class holds all the data related to an already loaded module.
 */
class LoadedInstance
{
public:
    /**
     * @brief Construct a new Loaded Instance object
     */
    LoadedInstance() = default;

    /**
     * @brief Destroy the Loaded Instance object
     * Unloads it automatically
     */
    ~LoadedInstance() { unload(); }

    /**
     * @brief Performs a load of a shared file
     * This functions opens the shared file and if it exists and there is no
     * error, loads it in memory.
     * @param fileName string containing the file name to load
     * @return if the file has been loaded successfully
     */
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

    /**
     * @brief Load one of the methods contained in the loaded instance.
     * The loaded instance has to have been already loaded to be able to load
     * one of its methods. If the method was already loaded, the cached value
     * will be returned
     * @param methodName Name of the method to be loaded
     * @return void const* Address containing the method or nullptr if error
     */
    [[nodiscard]] void const* loadMethod(char const* const methodName)
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

    /**
     * @brief Ask the instance if it has been successfully loaded
     * @return true on success
     */
    [[nodiscard]] bool loaded() const
    {
        return m_shared_file_handle != nullptr;
    }

    /**
     * @brief Ask the instance to unload.
     * If there were loaded methods, they will be deleted too.
     * @note You might reload the module after unloading it
     * @return If the unload has been performed
     */
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

    /**
     * @brief Raw access to the loaded data
     * @return void const* the data
     */
    [[nodiscard]] void const* loadedData() const
    {
        return m_shared_file_handle;
    }

private:
    void* m_shared_file_handle{nullptr};
    std::map<std::string, void*> m_methods{};
};
}  // namespace agl
