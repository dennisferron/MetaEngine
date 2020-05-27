project(Knife)

set(CMAKE_CXX_STANDARD 17)

set(KNIFE_0_INPUTS compiler.k)

set(KNIFE_0_OUTPUTS compiler.1.hpp
                    compiler.1.cpp
                    knife.1.db)

# Generate second stage Knife outputs.
add_custom_command(
        COMMAND Knife_0 --out-dir ${CMAKE_CURRENT_BINARY_DIR} --inputs ${KNIFE_0_INPUTS} --outputs ${KNIFE_0_OUTPUTS}
        DEPENDS Knife_0 ${KNIFE_0_INPUTS}
        OUTPUT ${KNIFE_0_OUTPUTS}
        COMMENT "Running Knife tool to generate Knife compiler sources."
)

add_executable(Knife_0
        main.cpp
        compiler.0.cpp
        compiler.0.hpp)

target_link_libraries( Knife_0 PUBLIC
        sqlite
)

add_executable(Knife
        main.cpp
        compiler.1.cpp
        compiler.1.hpp)

target_link_libraries( Knife PUBLIC
        sqlite
)
