cmake_minimum_required(VERSION 3.10)

project(R-Type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_DEBUG_POSTFIX d)

include(../cmake/automate-vcpkg.cmake)
vcpkg_bootstrap()
vcpkg_install_packages(raylib stduuid)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# The static permits to enter the functions, avoid settings the path to a .dll etc...
find_library(GEngine_LIB NAMES GEngine-sd PATHS ../build/Debug ../build)
# find_library(GEngine_LIB NAMES GEngined PATHS ../build/Debug ../build)
else()
find_library(GEngine_LIB NAMES GEngine PATHS ../build/Release ../build)
endif()

file(GLOB_RECURSE SOURCES source/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

find_package(raylib REQUIRED)

include_directories(include)
include_directories(../include)

add_executable(r-type_client ${SOURCES} ${HEADERS})
add_executable(r-type_server ${SOURCES} ${HEADERS})

if(WIN32)
target_link_libraries(r-type_client PRIVATE ${GEngine_LIB} raylib wsock32 ws2_32)
target_link_libraries(r-type_server PRIVATE ${GEngine_LIB} raylib wsock32 ws2_32)
else()
target_link_libraries(r-type_client PRIVATE ${GEngine_LIB} raylib)
target_link_libraries(r-type_server PRIVATE ${GEngine_LIB} raylib)
endif()

set_target_properties(r-type_client PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)
set_target_properties(r-type_server PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

install(TARGETS r-type_client r-type_server
    RUNTIME DESTINATION bin
)

target_compile_definitions(r-type_server PRIVATE Server)
target_compile_definitions(r-type_client PRIVATE Client)