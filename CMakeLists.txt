cmake_minimum_required(VERSION 3.13)
project(MetaEngine)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/cmake
)

include(UseBoost)
#include(UseBullet)
#include(UseIrrlicht)

add_subdirectory(bullet3)
add_subdirectory(irrlicht)
add_subdirectory(ThinPlateSpline)
add_subdirectory(Glue)
add_subdirectory(UnitTests)

add_executable(MetaEngine
        main.cpp)

# Note:  Order libraries in this list matters.  I know LinearMath and BulletCollision go at the bottom.
#  I'm less sure about the order of the rest of the Bullet libraries.
target_link_libraries( MetaEngine PUBLIC
        Glue
)

#set(CMAKE_VERBOSE_MAKEFILE ON)
