export module agloader:module;

import <memory>;

import :imodule;
import :linstance;

namespace agl
{
/**
 * @brief Class holding data of a loaded module
 * Module private implementation
 */
export class Module : public IModule
{
public:
    /**
     * @brief Default constructor
     */
    Module() noexcept = default;

    /**
     * @brief Construct a new Module object
     * @param loadedInstance a shared pointer to an already created instance
     * from LoadedInstance
     */
    explicit Module(std::shared_ptr<LoadedInstance> loadedInstance) noexcept :
        m_loadedInstance{std::move(loadedInstance)}
    {}

    /**
     * @brief Construct a new Module object from another one (copy)
     */
    Module(Module const&) = default;

    /**
     * @brief Assignment operator
     * @return Module& a new copy of the object
     */
    Module& operator=(Module const&) = default;

    /**
     * @brief Construct a new Module object taking ownership of another one
     * (move constructor)
     */
    Module(Module&&) = default;

    /**
     * @brief Move operator
     * @return Module& The assigned data (same as *this from this moment)
     */
    Module& operator=(Module&&) = default;

    /**
     * @brief Access to the internal pointer of the module
     * @return LoadedInstance* inner pointer
     */
    LoadedInstance* operator->() noexcept { return m_loadedInstance.get(); }

    /**
     * @brief Access to the internal pointer of the module
     * @return LoadedInstance* inner pointer
     */
    LoadedInstance const* operator->() const noexcept
    {
        return m_loadedInstance.get();
    }

    /**
     * @brief Equality comparator
     * 
     * @param rhs Right hand side of the comparator
     * @return They are equals or not
     */
    bool operator==(Module const& rhs) const
    {
        return m_loadedInstance.get() == rhs.m_loadedInstance.get();
    }

    /**
     * @brief Load a method.
     * Forward the call to the internal pointer
     * @param methodName String containing the file name
     * @return void const* Data loaded or nullptr
     */
    void const* loadMethod(char const* const methodName) override
    {
        return m_loadedInstance->loadMethod(methodName);
    }

private:
    std::shared_ptr<LoadedInstance> m_loadedInstance;
};

}  // namespace agl
