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

    explicit constexpr Module(
        std::shared_ptr<LoadedInstance> loadedInstance) noexcept :
        m_loadedInstance{std::move(loadedInstance)}
    {}

    constexpr LoadedInstance* operator->() noexcept
    {
        return m_loadedInstance.get();
    }

    constexpr LoadedInstance const* operator->() const noexcept
    {
        return m_loadedInstance.get();
    }

    constexpr bool operator==(Module const& rhs) const
    {
        return m_loadedInstance.get() == rhs.m_loadedInstance.get();
    }

private:
    std::shared_ptr<LoadedInstance> m_loadedInstance;
};

}  // namespace agl
