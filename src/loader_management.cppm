export module agloader:mngm;

import <memory>;

import :loader;

import "loader_export.hpp";

namespace
{
constinit std::unique_ptr<agl::Loader> loaderInstance;
constinit uintmax_t reference_counter{0U};
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
 * Decrements the reference counter for the Loader class. Deletes the loader if the reference counter reaches 0
 * @return The counter value after decrementing it. If it is 0, the Loader class will be destroyed
 */
export LOADER_API uintmax_t destroyLoader() noexcept
{
    if (reference_counter > 0U)
    {
        --reference_counter;
    }

    if (reference_counter == 0U)
    {
        loaderInstance.reset(nullptr);
    }
    return reference_counter;
}

/**
 * @return bool Is the loader active and ready?
 */
export LOADER_API bool isActive() noexcept
{
    return reference_counter != 0U;
}

/**
 * @return Number of instanciations of the class. Aka the number of reference counted objects created
 */
export LOADER_API uintmax_t instantiations() noexcept
{
    return reference_counter;
}

}  // namespace agl
