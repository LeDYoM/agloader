export module agloader:mngm;

import "loader_export.hpp";
import :loader;

namespace agl {
/**
 * @brief Create a Loader object
 * @return An instance of the loader class
 */
export LOADER_API Loader *createLoader();

/**
 * @brief Destroy the loader
 */
export LOADER_API void destroyLoader();

} // namespace agl
