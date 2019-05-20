cmake_minimum_required(VERSION 3.13)
project(ThinPlateSpline)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/../cmake
)

include(UseBoost)

add_library(ThinPlateSpline
        Include/ThinPlateSpline/ControlPoint.hpp
        Include/ThinPlateSpline/Demo.hpp
        Include/ThinPlateSpline/gauss-elim.h
        Include/ThinPlateSpline/linalg3d.h
        Include/ThinPlateSpline/ludecomposition.h
        Include/ThinPlateSpline/ThinPlateQuilt.hpp
        Include/ThinPlateSpline/ThinPlateSpline.hpp
        Source/2d-morph.cpp
        Source/ControlPoint.cpp
        Source/linalg3d.cpp
        Source/ThinPlateQuilt.cpp
        Source/ThinPlateSpline.cpp
        )

target_include_directories(ThinPlateSpline PUBLIC Include)
