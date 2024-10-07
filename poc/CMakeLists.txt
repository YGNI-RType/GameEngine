cmake_minimum_required(VERSION 3.10)
project(hagar-i-oop)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

include(cmake/automate-vcpkg-gengine.cmake)
vcpkg_bootstrap()
vcpkg_install_gengine()

include_directories(include)

file(GLOB_RECURSE SOURCES source/*.cpp)

add_executable(hagar-i-oop ${SOURCES})

find_package(GEngine CONFIG REQUIRED)
target_link_libraries(hagar-i-oop PRIVATE GEngine)
