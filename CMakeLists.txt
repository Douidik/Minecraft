cmake_minimum_required(VERSION 3.16)
project(Minecraft)
set(CMAKE_CXX_STANDARD 20) # Using C++20

# Set compiler flags for Clang compiler
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++ -lm -lpthread")

# Adding Dependencies
find_package(PkgConfig)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLM REQUIRED glm)
pkg_search_module(SPDLOG REQUIRED spdlog)
pkg_search_module(JSON REQUIRED nlohmann_json)

set(DEPENDENCIES_INCLUDES ${GLFW_INCLUDE_DIRS}
                          ${GLEW_INCLUDE_DIRS}
                          ${GLM_INCLUDE_DIRS}
                          ${SPDLOG_INCLUDE_DIRS}
                          ${JSON_INCLUDE_DIRS}
                          vendor/stb
                          vendor/PerlinNoise
    )

set(DEPENDENCIES_LIBRARIES ${GLFW_LIBRARIES}
                           ${GLEW_LIBRARIES}
                           ${GLM_LIBRARIES}
                           ${SPDLOG_LIBRARIES}
                           ${JSON_LIBRARIES}
    )


# Retrieving all sources
file(GLOB_RECURSE MINECRAFT_SOURCES src/*.cpp)
file(GLOB_RECURSE MINECRAFT_HEADERS src/*.h)

#Compiling Minecraft
add_executable(Minecraft ${MINECRAFT_SOURCES} ${MINECRAFT_HEADERS})

target_precompile_headers(Minecraft PUBLIC src/mc.pch)

target_link_libraries(Minecraft PUBLIC ${DEPENDENCIES_LIBRARIES})
target_include_directories(Minecraft PUBLIC ${DEPENDENCIES_INCLUDES} src/)