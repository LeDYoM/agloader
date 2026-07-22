import agloader;
import <cassert>;

void test0()
{
    auto* loader{agl::createLoader()};
    assert(loader);
    auto* mod{loader->loadModule("agloader_test_lib")};
    assert(mod);
    agl::destroyLoader();
}

void test1()
{
    auto* loader{agl::createLoader()};
    loader->loadModule("agloader_test_lib");
    agl::destroyLoader();
}

int main(int, char*[])
{
    test0();
//    test1();
    return 0;
}
