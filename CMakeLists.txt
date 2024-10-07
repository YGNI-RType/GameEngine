cmake_minimum_required(VERSION 3.10)
project(GEngine)

include(GNUInstallDirs)

include(cmake/automate-vcpkg.cmake)
vcpkg_bootstrap()
vcpkg_install_packages(raylib)

file(GLOB_RECURSE SOURCES source/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX ".*/deprecated/.*")

file(GLOB_RECURSE HEADERS include/*.h)
list(FILTER HEADERS EXCLUDE REGEX ".*/deprecated/.*")

include_directories(include)

if(NOT WIN32)
    add_compile_options(-Wall -Wextra)
endif()

add_library(GEngine SHARED ${SOURCES} ${HEADERS})
add_library(GEngine_static STATIC ${SOURCES} ${HEADERS})

if(WIN32)
  target_link_libraries(GEngine wsock32 ws2_32)
  target_link_libraries(GEngine_static wsock32 ws2_32)
endif()

set(CMAKE_DEBUG_POSTFIX d)
set_target_properties(GEngine PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    VERSION 0.0.1
)
set_target_properties(GEngine_static PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    VERSION 0.0.1
    OUTPUT_NAME "GEngine"
)

find_package(raylib CONFIG REQUIRED)
target_link_libraries(GEngine raylib)
target_link_libraries(GEngine_static raylib)

install(TARGETS GEngine GEngine_static
        EXPORT GEngine_targets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install(DIRECTORY include/ DESTINATION include)

install(EXPORT GEngine_targets
        FILE GEngineTargets.cmake
        DESTINATION share/GEngine)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/GEngineConfig.cmake"
"include(CMakeFindDependencyMacro)\n"
"find_dependency(raylib CONFIG REQUIRED)\n"
"include(\"\${CMAKE_CURRENT_LIST_DIR}/GEngineTargets.cmake\")\n"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/GEngineConfig.cmake"
        DESTINATION share/GEngine)
