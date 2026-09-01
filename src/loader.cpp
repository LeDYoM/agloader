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
    LOADER_PRIVATE Loader();

    /**
     * @brief Destroy the Loader object.
     * Destructor. Do not use it directly.
     */
    LOADER_PRIVATE ~Loader();

    /**
     * @brief Load a shared library module from a file
     * @param fileName File to load WITHOUT extension
     * @return Reference to a reference to an opaque @b IModule object
     */
    LOADER_API IModule* loadModule(char const* const fileName);

    /**
     * @brief Unload a module from a shared library.
     * @param fileName File containing the already loaded module
     * @return If the unloading was successful or not
     */
    LOADER_API bool unloadModule(IModule* mod);

    LOADER_API uint64_t loadedModules() const noexcept
    {
        return static_cast<uint32_t>(m_loadedInstances.size());
    }

    LOADER_API bool empty() const noexcept
    {
        return m_loadedInstances.empty();
    }

private:
    std::map<std::string, Module> m_loadedInstances;
};

}  // namespace agl
