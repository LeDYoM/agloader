export module agloader:utils;

import <string>;

namespace agl
{
    /*
bool formatFileName(char const* const fileName,
                    char const* const paramExtension,
                    char const* const paramPrefix,
                    char result[256])
{
    result[0] = 0;
    auto const sizeFileName{std::strlen(fileName)};
    auto const sizeParamExtension{std::strlen(paramExtension)};

    if (sizeFileName < sizeParamExtension)
    {
        return false;
    }

    std::make_signed<decltype(sizeFileName)> counterFileName{sizeFileName - 1};
    std::make_signed<decltype(sizeParamExtension)> counterParamExtension{
        sizeParamExtension - 1};

    while (counterFileName > -1 && counterParamExtension > -1 &&
           fileName[sizeFileName] == paramExtension[sizeParamExtension])
    {
        --sizeFileName;
        --sizeParamExtension;
    }


    if (!fileName.ends_with(param_extension))
    {
        fileName += param_extension;
    }

    return param_prefix + fileName;
}
*/
}  // namespace agl
