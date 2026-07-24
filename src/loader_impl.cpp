module agloader;

import <string>;
import <memory>;

import :module;

namespace agl
{
Module& fromIModule(IModule const& mod)
{
    // Do not do that.
    return const_cast<Module&>(static_cast<Module const&>(mod));
}

Loader::Loader() = default;

Loader::~Loader() = default;

void const* Loader::loadModule(const char* const fileName)
{
    auto loadedInstace{std::make_shared<LoadedInstance>()};
    if (loadedInstace->load(fileName))
    {
        m_loaded_instances[fileName] = Module{loadedInstace};
    }
    return loadedInstace.get();
}

IModule const& Loader::loadModule2(const char* const fileName)
{
    auto const [it, result]{m_loaded_instances.insert({fileName, {}})};
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

void const* Loader::loadMethod2(IModule const& mod,
                                const char* const methodName)
{
    if (auto& real_module{fromIModule(mod)}; real_module->loaded())
    {
        return real_module->loadMethod(methodName);
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
