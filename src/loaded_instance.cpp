module;

#include <map>
#include <string>

export module agloader:linstance;

namespace agl
{
class LoadedInstance
{
public:
    LoadedInstance();
    ~LoadedInstance();

    bool load(const char* fileName);
    void const* loadMethod(const char* methodName);
    bool loaded() const;
    bool unload();
    void const* loadedData() const { return m_shared_file_handle; }

private:
    void* m_shared_file_handle{nullptr};
    std::map<std::string, void*> m_methods;
};
}  // namespace agl
