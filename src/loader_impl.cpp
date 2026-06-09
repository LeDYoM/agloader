module;

#include <string>
#include <memory>

module agloader;

namespace agl
{
Loader::Loader() = default;

Loader::~Loader() = default;

void const* Loader::loadModule(const char* const fileName)
{
    auto loadedInstace{std::make_shared<LoadedInstance>()};
    loadedInstace->load(fileName);

    if (loadedInstace->loaded())
    {
        m_loaded_instances[fileName] = loadedInstace;
    }
    return loadedInstace->loadedData();
}

void const* Loader::loadMethod(const char* const fileName,
                               const char* const methodName)
{
    if (auto const iterator{m_loaded_instances.find(fileName)};
        iterator != m_loaded_instances.end())
    {
        auto loadedInstance{(*iterator).second};
        return loadedInstance->loadMethod(methodName);
    }
    return nullptr;
}

bool Loader::unloadModule(const char* const fileName)
{
    if (auto const iterator{m_loaded_instances.find(fileName)};
        iterator != m_loaded_instances.end())
    {
        m_loaded_instances.erase(iterator);
        return true;
    }

    return false;
}

}  // namespace agl
