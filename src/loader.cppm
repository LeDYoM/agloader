export module agloader:loader;

import <map>;
import <string>;
import <memory>;
import <cassert>;

import "loader_export.hpp";
import :linstance;
import :imodule;
import :module;

namespace agl
{
/**
 * @brief Main class of the library to load module files
 * This class provides the basic API to load a module and its methods
 */
export class Loader
{
public:
    /**
     * @brief Construct a new Loader objec.
     * Default constructor. Do not use it directly.
     */
    LOADER_PRIVATE Loader() = default;

    /**
     * @brief Destroy the Loader object.
     * Destructor. Do not use it directly.
     */
    LOADER_PRIVATE ~Loader() = default;

    /**
     * @brief Load a shared library module from a file
     * @param fileName File to load WITHOUT extension
     * @return Reference to a reference to an opaque @b IModule object
     */
    LOADER_API IModule* loadModule(char const* const fileName)
    {
        auto it_found{m_loadedInstances.find(fileName)};
        if (it_found == m_loadedInstances.end())
        {
            auto instance{std::make_shared<LoadedInstance>()};
            if (instance->load(fileName))
            {
                Module result_module{std::move(instance)};
                auto [it, result]{m_loadedInstances.insert_or_assign(
                    fileName, std::move(result_module))};
                (void)(result);
                return &(it->second);
            }
            else
            {
                return nullptr;
            }
        }
        return &(it_found->second);
    }

    /**
     * @brief Unload a module from a shared library.
     * @param mod Pointer to IModule object.
     * @return If the unloading was successful or not
     */
    LOADER_API bool unloadModule(IModule* mod)
    {
        if (mod != nullptr)
        {
            std::string const* key_element{nullptr};

            for (auto& element : m_loadedInstances)
            {
                if (&(element.second) == mod)
                {
                    element.second->unload();
                    assert(key_element == nullptr);
                    key_element = &element.first;
                }
            }

            if (key_element != nullptr)
            {
                assert(!m_loadedInstances.empty());
                m_loadedInstances.erase(*key_element);
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Get the number of loaded modules
     * @return uint64_t The number of loaded modules
     */
    LOADER_API uint64_t loadedModules() const noexcept
    {
        return static_cast<uint64_t>(m_loadedInstances.size());
    }

    /**
     * @brief Ask the library if there is currently any loaded module
     * @return Is the list of loaded modules empty?
     */
    LOADER_API bool empty() const noexcept { return m_loadedInstances.empty(); }

private:
    LOADER_PRIVATE std::map<std::string, Module> m_loadedInstances;
};

}  // namespace agl
