import agloader;
import <cassert>;
import <cstdint>;

using getNumber1_t = int32_t (*)(int16_t const);

void test1()
{
    auto* loader{agl::createLoader()};
    assert(loader);

    agl::IModule& mod{loader->loadModule("agloader_test_lib")};

    {
        auto result_fun{
            static_cast<getNumber1_t>(loader->loadMethod(mod, "getNumber1"))};
        assert(result_fun);

        int32_t const result{result_fun(10)};
        assert(result == 11);
    }

    {
        auto result_fun{loader->loadMethod<getNumber1_t>(mod, "getNumber1")};
        assert(result_fun);

        int32_t const result{result_fun(100)};
        assert(result == 101);
    }

        {
        auto result_fun{
            static_cast<getNumber1_t>(loader->loadMethod(mod, "getNumber1"))};
        assert(result_fun);

        int32_t const result{result_fun(10)};
        assert(result == 11);
    }

    {
        auto result_fun{loader->loadMethod<getNumber1_t>(mod, "getNumber")};
        assert(!result_fun);
    }

    agl::destroyLoader();
}

int main(int, char*[])
{
    test1();
    return 0;
}
