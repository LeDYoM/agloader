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
    LOADER_API IModule& loadModule(const char* const fileName);

    /**
     * @brief Unload a module from a shared library.
     * @param fileName File containing the already loaded module
     * @return If the unloading was successful or not
     */
    LOADER_API bool unloadModule(const char* const fileName);

    /**
     * @brief Load a method from an already loaded module
     * @param mod Reference to a @b IModule object that is a result from a call
     * to @b loadModule
     * @param methodName Method to load
     * @return Pointer to the loaded method
     */
    LOADER_API void const* loadMethod(IModule& mod,
                                      const char* const methodName);

    /**
     * @brief Load a method from an already loaded module
     * @tparam T Type to load
     * @param mod Reference to a @b IModule object that is a result from a call
     * to @b loadModule
     * @param methodName Method to load
     * @return Pointer to the loaded method.
     */
    template <typename T>
    T loadMethod(IModule& mod, const char* const methodName)
    {
        return static_cast<T>(loadMethod(mod, methodName));
    }

    /**
     * @overload
     * @brief Load a method from an already loaded module
     * @param fileName File name containing the already loaded module.
     * @param methodName Method to load
     * @return Pointer to the loaded method.
     */
    LOADER_API void const* loadMethod(IModule const* imodule,
                                      const char* const methodName);

    /**
     * @overload
     * @brief Load a method from an already loaded module
     *
     * @tparam T Type to load
     * @param fileName File name containing the already loaded module.
     * @param methodName Method to load
     * @return Pointer to the loaded method.
     */
    template <typename T>
    T loadMethod(IModule const* imodule, const char* const methodName)
    {
        return reinterpret_cast<T>(loadMethod(imodule, methodName));
    }

private:
    std::map<std::string, Module> m_loaded_instances;
};

}  // namespace agl
