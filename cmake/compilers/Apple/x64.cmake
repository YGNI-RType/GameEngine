# Set the system name
set(CMAKE_SYSTEM_NAME Darwin)

# Set the C and C++ compilers
set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

# Set the target architecture
set(CMAKE_OSX_ARCHITECTURES "x86_64")

# Set the sysroot (if needed)
# set(CMAKE_SYSROOT /path/to/sysroot)

# Set the C and C++ flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch ${CMAKE_OSX_ARCHITECTURES}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch ${CMAKE_OSX_ARCHITECTURES}")

# Set the linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -arch ${CMAKE_OSX_ARCHITECTURES}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -arch ${CMAKE_OSX_ARCHITECTURES}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -arch ${CMAKE_OSX_ARCHITECTURES}")

# Set the find root path
# set(CMAKE_FIND_ROOT_PATH /path/to/find/root)

# Set the search paths for libraries and includes
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
