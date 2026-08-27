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

IModule& Loader::loadModule(const char* const fileName)
{
    auto const [it, result]{m_loadedInstances.insert({fileName, {}})};
    if (result)
    {
        it->second = Module{std::make_shared<LoadedInstance>()};
    }

    if (!it->second->loaded())
    {
        it->second->load(fileName);
    }

    return it->second;
}

bool Loader::unloadModule(IModule&& mod)
{
    std::string const* key_element{nullptr};

    for (auto& element : m_loadedInstances)
    {
        if (&(element.second) == &mod)
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

void const* Loader::loadMethod(IModule& mod, const char* const methodName)
{
    if (auto& real_module{fromIModule(mod)}; real_module->loaded())
    {
        return real_module->loadMethod(methodName);
    }
    return nullptr;
}

}  // namespace agl
