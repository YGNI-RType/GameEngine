## How to install the GEngine to your project

- Copy the `cmake` folder present in the `install` folder to your project root.
- Copy the `overlay-ports` folder present in the `install` folder to your project root.
- Add the following lines at the begin of your `CMakeLists.txt` file:

```cmake
include(cmake/automate-vcpkg-gengine.cmake)
vcpkg_bootstrap()
vcpkg_install_gengine()
```

> It will install vcpkg and the GEngine package with all its dependencies.

- Add the following lines at the end of your `CMakeLists.txt` file:

```cmake
find_package(GEngine CONFIG REQUIRED)
target_link_libraries(main PRIVATE GEngine)
```

> It will link the GEngine to your project.
