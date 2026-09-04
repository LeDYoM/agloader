export module agloader:mngm;

import <memory>;

import :loader;

import "loader_export.hpp";

namespace
{
static constinit std::unique_ptr<agl::Loader> loaderInstance;
static constinit uintmax_t reference_counter{0U};
}  // namespace

namespace agl
{
/**
 * @brief Create a Loader object
 * @return An instance of the loader class
 */
export LOADER_API Loader* createLoader()
{
    ++reference_counter;
    if (loaderInstance == nullptr)
    {
        loaderInstance = std::make_unique<Loader>();
    }

    return loaderInstance.get();
}

/**
 * @brief Destroy the loader
 */
export LOADER_API void destroyLoader() noexcept
{
    if (reference_counter > 0U)
    {
        --reference_counter;
    }

    if (reference_counter == 0U)
    {
        loaderInstance.reset(nullptr);
    }
}

export LOADER_API bool isActive() noexcept
{
    return reference_counter == 0;
}

export LOADER_API uintmax_t instantiations() noexcept
{
    return reference_counter;
}

}  // namespace agl
