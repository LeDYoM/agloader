import agloader;
import <cassert>;
import <cstdint>;

using getNumber1_t = int32_t (*)(int16_t const);

void test1()
{
    auto* loader{agl::createLoader()};
    assert(loader);

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
    }

    {
        auto result_fun{mod->loadMethod<getNumber1_t>("getNumber1")};
        assert(result_fun);

        int32_t const result{result_fun(100)};
        assert(result == 101);
    }

    {
        auto result_fun{
            static_cast<getNumber1_t>(mod->loadMethod("getNumber1"))};
        assert(result_fun);

        int32_t const result{result_fun(10)};
        assert(result == 11);
    }

    {
        auto result_fun{mod->loadMethod<getNumber1_t>("getNumber")};
        assert(!result_fun);
    }

    agl::destroyLoader();
}

int main(int, char*[])
{
    test1();
    return 0;
}
