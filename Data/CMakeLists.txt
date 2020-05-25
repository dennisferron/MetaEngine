cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/../cmake
)

include(UseBoost)

set(GAMEDATA_KNIFE_INPUTS gamedata.k)

set(GAMEDATA_KNIFE_HEADERS
        gamedata.hpp)

set(GAMEDATA_KNIFE_OUTPUTS
        gamedata.cpp
        gamedata.db)

# Generating header files separately helps avoid circular dependencies between targets.
add_custom_command(
        COMMAND Knife --out-dir ${CMAKE_CURRENT_BINARY_DIR} --inputs ${GAMEDATA_KNIFE_INPUTS} --outputs ${GAMEDATA_KNIFE_HEADERS}
        DEPENDS Knife ${GAMEDATA_KNIFE_INPUTS}
        OUTPUT ${GAMEDATA_KNIFE_HEADERS}
        COMMENT "Running Knife tool to generate game data headers."
)

# Other targets with .cpp files which include the .hpp file(s) generated here can use
# add_dependency on this custom target to ensure these header(s) get generated first.
#[[
add_custom_target(
        generate-gamedata-headers
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/../Data/gamedata.hpp
)
]]

# Finally we generate the .cpp and database outputs.
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
