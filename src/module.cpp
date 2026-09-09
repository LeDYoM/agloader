export module agloader:module;

import <memory>;

import :imodule;
import :linstance;

namespace agl
{
/**
 * @brief Class holding data of a loaded module
 */
export class Module : public IModule
{
public:
    Module() noexcept = default;

    explicit Module(
        std::shared_ptr<LoadedInstance> loadedInstance) noexcept :
        m_loadedInstance{std::move(loadedInstance)}
    {}

    Module(Module const&)            = default;
    Module& operator=(Module const&) = default;

    LoadedInstance* operator->() noexcept
    {
        return m_loadedInstance.get();
    }

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
