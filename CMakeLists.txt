cmake_minimum_required(VERSION 3.13)
project(MetaEngine)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/cmake
)

include(UseBoost)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(Knife)
add_subdirectory(bullet3)
add_subdirectory(irrlicht)
add_subdirectory(ThinPlateSpline)
add_subdirectory(Glue)
add_subdirectory(Data)
add_subdirectory(UnitTests)
add_subdirectory(sqlite)

add_executable(MetaEngine
        main.cpp)

target_link_libraries( MetaEngine PUBLIC
        Glue
        GameData
)
