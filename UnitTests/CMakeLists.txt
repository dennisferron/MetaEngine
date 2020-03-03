find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})

add_executable(UnitTests
        TestMain.cpp
        DatabaseTests.cpp
        BulletComponentTests.cpp
        GraphTests.cpp
        ModelMocks.hpp BulletMocks.hpp)

target_link_libraries( UnitTests PUBLIC
        Glue
    )
