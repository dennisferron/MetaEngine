find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})

add_executable(UnitTests_Finagle
        Test/testmain.cpp
        Test/TestEngineRules.cpp
        Test/TestTMS.cpp
        )

#[[
target_link_libraries( UnitTests_Finagle PUBLIC
        Glue
    )
]]
