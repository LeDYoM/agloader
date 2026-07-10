export module agloader:module;

import <memory>;

import :imodule;
import :linstance;

namespace agl {
/**
 * @brief Class holding data of a loaded module
 */
export class Module : public IModule {
public:
  explicit constexpr Module(
      std::shared_ptr<LoadedInstance> loadedInstance) noexcept
      : m_loadedInstance{std::move(loadedInstance)} {}

  constexpr std::shared_ptr<LoadedInstance> loadedInstance() const noexcept {
    return m_loadedInstance;
  }

private:
  std::shared_ptr<LoadedInstance> m_loadedInstance;
};

} // namespace agl
