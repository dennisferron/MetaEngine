cmake_minimum_required(VERSION 3.13)
project(sqlite)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/../cmake
)

add_compile_definitions(SQLITE_ENABLE_JSON1)

add_library(sqlite
	sqlite3.h
	sqlite3.c
        )

target_include_directories(sqlite PUBLIC .)
