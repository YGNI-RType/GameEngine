set(CMAKE_SYSTEM_NAME Windows)

# Specify the target architecture
set(CMAKE_SYSTEM_PROCESSOR x86)

# Set the C and C++ compilers to use MSVC
set(CMAKE_C_COMPILER "cl.exe")
set(CMAKE_CXX_COMPILER "cl.exe")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /arch:IA32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:IA32")

# Set the platform to x86
set(CMAKE_GENERATOR_PLATFORM "Win32" CACHE STRING "CMake generator platform" FORCE)

# Set the CMake find root path mode to only search in the specified directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
