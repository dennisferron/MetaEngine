find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})

add_executable(UnitTests TestMain.cpp Example.cpp)

target_link_libraries( UnitTests PUBLIC
        Glue
    )
