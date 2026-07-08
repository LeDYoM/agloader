export module agloader:module;

import :imodule;

namespace agl {
/**
 * @brief Class holding data of a loaded module
 */
export class Module : public IModule {
public:
    explicit Module(const void* module) : m_module{module} {}

    constexpr const void* moduleData() const noexcept { return m_module; }

private:
    const void *m_module;
};

} // namespace agl
