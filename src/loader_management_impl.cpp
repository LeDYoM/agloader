module agloader;

import <memory>;

import :mngm;

import :loader;

namespace agl {
namespace {
static constinit std::unique_ptr<Loader> loaderInstance;
static constinit uintmax_t reference_counter{0U};
} // namespace

Loader *createLoader() {
  ++reference_counter;
  if (loaderInstance == nullptr) {
    loaderInstance = std::make_unique<Loader>();
  }

  return loaderInstance.get();
}

void destroyLoader() {
  if (reference_counter > 0U) {
    --reference_counter;
  }

  if (reference_counter == 0U) {
    loaderInstance.reset(nullptr);
  }
}

} // namespace agl
