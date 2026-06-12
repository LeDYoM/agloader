# agloader
Simple C++ library to open dynamic linked libraries directly without linking or prelinking

This library is a library that helps loading other libaries/extensions/plugins.

## Sample

Here is a sample of usage of the library

You would need no import the library:

```cpp
import agloader;
```

Then, to initialize the library, you must execute its initialization function:

```cpp
    auto* loader{agl::createLoader()};
```

This will return an instance to the loader class where you can use the loader functionality. (Or nullptr in case of error).
Assuming it is not nullptr, you can then load a module:

```cpp
    auto* loader{agl::createLoader()};
```

```cpp
int main() {}
```