
find_package(Irrlicht REQUIRED
    NO_MODULE
    PATHS irrlicht/cmake-build-debug)

if(Irrlicht_FOUND)

    message(STATUS "Found Irrlicht")

    include_directories(${Irrlicht_INCLUDE_DIRS})

    add_definitions     ( ${Irrlicht_DEFINITIONS} )
    include_directories ( ${Irrlicht_INCLUDE_DIRS} )
    link_directories    ( ${Irrlicht_LIBRARY_DIRS} )

    link_directories(
            irrlicht/cmake-build-debug/
    )
    link_libraries(
            ${Irrlicht_LIBRARIES}
    )
else()
    message(SEND_ERROR "Irrlicht is required for MetaEngine")
endif()

