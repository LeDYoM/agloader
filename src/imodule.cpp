export module agloader:imodule;

import "loader_export.hpp";

namespace agl
{
/**
 * @brief Main class to load a module
 * This class provides the basic API to load a module and its methods
 */
export class IModule
{
public:
    IModule() = default;

    /**
     * @brief Load a method from an already loaded module
     * @param mod Reference to a @b IModule object that is a result from a call
     * to @b loadModule
     * @param methodName Method to load
     * @return Pointer to the loaded method
     */
    LOADER_API virtual void const* loadMethod(char const* const methodName) = 0;

    /**
     * @brief Load a method from an already loaded module
     * @tparam T Type to load
     * @param mod Reference to a @b IModule object that is a result from a call
     * to @b loadModule
     * @param methodName Method to load
     * @return Pointer to the loaded method.
     */
    template <typename T>
    T loadMethod(char const* const methodName)
    {
        return static_cast<T>(loadMethod(methodName));
    }

protected:
    IModule(IModule const&)            = default;
    IModule& operator=(IModule const&) = default;

    virtual ~IModule() = default;
};

}  // namespace agl
