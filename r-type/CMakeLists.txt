cmake_minimum_required(VERSION 3.10)

project(R-Type)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_DEBUG_POSTFIX d)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
# The static permits to enter the functions, avoid settings the path to a .dll etc...
find_library(GEngine_LIB NAMES GEngine-sd PATHS ../build/Debug ../build)
# find_library(GEngine_LIB NAMES GEngined PATHS ../build/Debug ../build)
else()
find_library(GEngine_LIB NAMES GEngine PATHS ../build/Release ../build)
endif()

file(GLOB_RECURSE CLIENT_SOURCES client/*.cpp)
file(GLOB_RECURSE SERVER_SOURCES server/*.cpp)
file(GLOB_RECURSE SHARED_SOURCES shared/*.cpp)
file(GLOB_RECURSE HEADERS ../include/*.h)

include_directories(../include)

add_executable(r-type_client ${CLIENT_SOURCES} ${SHARED_SOURCES} ${HEADERS})
add_executable(r-type_server ${SERVER_SOURCES} ${SHARED_SOURCES} ${HEADERS})

if(WIN32)
target_link_libraries(r-type_client PRIVATE ${GEngine_LIB} wsock32 ws2_32)
target_link_libraries(r-type_server PRIVATE ${GEngine_LIB} wsock32 ws2_32)
else()
target_link_libraries(r-type_client PRIVATE ${GEngine_LIB})
target_link_libraries(r-type_server PRIVATE ${GEngine_LIB})
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
