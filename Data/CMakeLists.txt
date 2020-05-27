cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/../cmake
)

include(UseBoost)

set(GAMEDATA_KNIFE_INPUTS gamedata.k)

set(GAMEDATA_KNIFE_OUTPUTS  gamedata.hpp
                            gamedata.cpp
                            gamedata.db)

# Generate hpp, cpp, and db from gamedata .k files.
add_custom_command(
        COMMAND Knife --out-dir ${CMAKE_CURRENT_BINARY_DIR} --inputs ${GAMEDATA_KNIFE_INPUTS} --outputs ${GAMEDATA_KNIFE_OUTPUTS}
        DEPENDS Knife ${GAMEDATA_KNIFE_INPUTS}
        OUTPUT ${GAMEDATA_KNIFE_OUTPUTS}
        COMMENT "Running Knife tool to generate game data implementation and database."
)

add_library(GameData
        gamedata.cpp
        gamedata.hpp
)

target_include_directories(GameData PUBLIC ${CMAKE_BINARY_DIR}/Data
        ../Glue/Include
)
