export module agloader:imodule;

import "loader_export.hpp";

namespace agl
{
/**
 * @brief Class representing a loaded module to public interface
 * This class provides the basic API to load a module and its methods
 */
export class IModule
{
public:
    LOADER_PRIVATE IModule() noexcept = default;

    /**
     * @brief Load a method from an already loaded module
     * @param methodName Method name to load. Name mangling applies
     * @return Pointer to the loaded method or nullptr if error
     */
    LOADER_API virtual void const* loadMethod(char const* methodName) = 0;

    /**
     * @brief Load a method from an already loaded module
     * @tparam T Type to load
     * @param methodName Method name to load. Name mangling applies
     * @return Pointer to the loaded method or nullptr if error
     * @note If the method signature pass as parameter does not correspond to
     * the real method signature, there is UB.
     */
    template <typename T>
    T loadMethod(char const* const methodName)
    {
        return static_cast<T>(loadMethod(methodName));
    }

protected:
    IModule(IModule const&)            = default;
    IModule& operator=(IModule const&) = default;
    IModule(IModule&&)                 = default;
    IModule& operator=(IModule&&)      = default;

    virtual ~IModule() = default;
};

}  // namespace agl
