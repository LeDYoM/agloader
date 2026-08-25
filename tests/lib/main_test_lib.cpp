import "main_test_lib_export.hpp";
import <cstdint>;

int main(int, char*[])
{
    return 0;
}

extern "C"
{
    LOADER_TEST_API int32_t getNumber1(int16_t const param1)
    {
        return param1 + 1;
    }
}
