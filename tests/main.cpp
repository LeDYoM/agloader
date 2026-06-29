import agloader;

int main(int , char *[])
{
    auto* loader{agl::createLoader()};
    (void)(loader);
    agl::destroyLoader();
    return 0;
}
