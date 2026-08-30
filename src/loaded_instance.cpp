export module agloader:linstance;

import <map>;
import <string>;

namespace agl
{
class LoadedInstance
{
public:
    LoadedInstance();
    ~LoadedInstance();

    bool load(char const* const fileName);
    void const* loadMethod(char const* const methodName);
    bool loaded() const;
    bool unload();
    void const* loadedData() const;

private:
    void* m_shared_file_handle{nullptr};
    std::map<std::string, void*> m_methods;
};
}  // namespace agl
