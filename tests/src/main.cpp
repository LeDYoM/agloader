import agloader;
import <cassert>;
import <cstdint>;
import <utility>;

using getNumber1_t = int32_t (*)(int16_t const);

void test1()
{
    assert(agl::instantiations() == 0U);
    assert(!agl::isActive());

    auto* loader_tmp{agl::createLoader()};
    assert(loader_tmp);
    assert(agl::instantiations() == 1U);
    assert(agl::isActive());
    std::ignore = loader_tmp;

    auto* loader{agl::createLoader()};
    assert(loader);
    assert(agl::instantiations() == 2U);
    assert(agl::isActive());

    assert(loader->empty());
    assert(loader->loadedModules() == 0U);

    agl::IModule* mod{loader->loadModule("agloader_test_lib")};
    assert(mod);
    assert(!(loader->empty()));
    assert(loader->loadedModules() == 1U);

    {
        auto result_fun{
            static_cast<getNumber1_t>(mod->loadMethod("getNumber1"))};
        assert(result_fun);

        int32_t const result{result_fun(10)};
        assert(result == 11);
        std::ignore = result;
    }

    {
        auto result_fun{mod->loadMethod<getNumber1_t>("getNumber1")};
        assert(result_fun);

        int32_t const result{result_fun(100)};
        assert(result == 101);
        std::ignore = result;
    }

    {
        auto result_fun{
            static_cast<getNumber1_t>(mod->loadMethod("getNumber1"))};
        assert(result_fun);

        int32_t const result{result_fun(10)};
        assert(result == 11);
        std::ignore = result;
    }

    {
        auto result_fun{mod->loadMethod<getNumber1_t>("getNumber")};
        assert(!result_fun);
        std::ignore = result_fun;
    }

    {
        agl::IModule* mod2{loader->loadModule("./agloader_test_lib")};
        assert(mod2);
        assert(!(loader->empty()));
        assert(loader->loadedModules() == 2U);
        std::ignore = mod2;

        {
            auto result_fun{
                static_cast<getNumber1_t>(mod->loadMethod("getNumber1"))};
            assert(!result_fun);
            std::ignore = result_fun;
        }

        {
            auto result_fun{mod->loadMethod("getNumber1")};
            assert(!result_fun);
            std::ignore = result_fun;
        }

        assert(loader->unloadModule(mod2));
        assert(!loader->unloadModule(mod2));
        assert(!loader->unloadModule(nullptr));
        assert(!(loader->empty()));
        assert(loader->loadedModules() == 1U);
    }

    {
        agl::IModule* mod2{loader->loadModule("agloader_test_lib.dll")};
        assert(!mod2);
        assert(!(loader->empty()));
        assert(loader->loadedModules() == 1U);
        std::ignore = mod2;
    }

    assert(agl::destroyLoader() == 1U);

    assert(agl::instantiations() == 1U);
    assert(agl::isActive());

    assert(agl::destroyLoader() == 0U);

    assert(agl::instantiations() == 0U);
    assert(!agl::isActive());
}

#pragma warning(push)
#pragma warning(disable : 4711)

int main(int, char*[])
{
    test1();
    return 0;
}
#pragma warning(pop)
