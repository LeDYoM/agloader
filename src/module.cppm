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

    explicit Module(std::shared_ptr<LoadedInstance> loadedInstance) noexcept :
        m_loadedInstance{std::move(loadedInstance)}
    {}

    /**
     * @brief Construct a new Module object from another one (copy)
     */
    Module(Module const&)            = default;

    /**
     * @brief Assignment operator
     * @return Module& a new copy of the object
     */
    Module& operator=(Module const&) = default;

    /**
     * @brief Construct a new Module object taking ownership of another one (move constructor)
     */
    Module(Module&&)                 = default;

    /**
     * @brief Move operator
     * @return Module& The assigned data (same as *this from this moment)
     */
    Module& operator=(Module&&)      = default;

    LoadedInstance* operator->() noexcept { return m_loadedInstance.get(); }

    LoadedInstance const* operator->() const noexcept
    {
        return m_loadedInstance.get();
    }

    bool operator==(Module const& rhs) const
    {
        return m_loadedInstance.get() == rhs.m_loadedInstance.get();
    }

    void const* loadMethod(char const* const methodName) override
    {
        return m_loadedInstance->loadMethod(methodName);
    }

private:
    std::shared_ptr<LoadedInstance> m_loadedInstance;
};

}  // namespace agl
