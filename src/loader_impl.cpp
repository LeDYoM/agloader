module agloader;

import <string>;
import <memory>;

import :module;

namespace agl
{
Module& fromIModule(IModule& mod)
{
    // Do not do that.
    return static_cast<Module&>(mod);
}

Loader::Loader() = default;

Loader::~Loader()
{
    for (auto& element : m_loadedInstances)
    {
        element.second->unload();
    }
    m_loadedInstances.clear();
}

IModule* Loader::loadModule(char const* const fileName)
{
    auto it_found{m_loadedInstances.find(fileName)};
    if (it_found == m_loadedInstances.end())
    {
        auto instance{std::make_shared<LoadedInstance>()};
        if (instance->load(fileName))
        {
            Module result_module{std::move(instance)};
            auto [it, result]{m_loadedInstances.insert_or_assign(
                fileName, std::move(result_module))};
            (void)(result);
            return &(it->second);
        }
        else
        {
            return nullptr;
        }
    }
    return &(it_found->second);
}

bool Loader::unloadModule(IModule* mod)
{
    std::string const* key_element{nullptr};

    for (auto& element : m_loadedInstances)
    {
        if (&(element.second) == mod)
        {
            element.second->unload();
            key_element = &element.first;
        }
    }

    if (key_element != nullptr)
    {
        m_loadedInstances.erase(*key_element);
        return true;
    }
    return false;
}

}  // namespace agl
