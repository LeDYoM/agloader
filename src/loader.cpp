export module agloader:loader;

import <map>;
import <string>;
import <memory>;

import "loader_export.hpp";
import :linstance;
import :imodule;
import :module;

namespace agl
{
/**
 * @brief Main class to load a module
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
    LOADER_PRIVATE ~Loader()
    {
        for (auto& element : m_loadedInstances)
        {
            element.second->unload();
        }
        m_loadedInstances.clear();
    }

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
     * @param fileName File containing the already loaded module
     * @return If the unloading was successful or not
     */
    LOADER_API bool unloadModule(IModule* mod)
    {
        std::string const* key_element{nullptr};

        for (auto& element : m_loadedInstances)
        {
            if (&(element.second) == mod)
            {
                element.second->unload();
                key_element = &element.first;
            }
        }

        if (key_element != nullptr)
        {
            m_loadedInstances.erase(*key_element);
            return true;
        }
        return false;
    }

    LOADER_API uint64_t loadedModules() const noexcept
    {
        return static_cast<uint32_t>(m_loadedInstances.size());
    }

    LOADER_API bool empty() const noexcept { return m_loadedInstances.empty(); }

private:
    std::map<std::string, Module> m_loadedInstances;
};

}  // namespace agl
