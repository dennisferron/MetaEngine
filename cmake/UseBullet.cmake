
find_package(Bullet REQUIRED
    LinearMath
    Bullet3Common
    BulletInverseDynamics
    BulletCollision
    BulletDynamics
    BulletSoftBody
    NO_MODULE
    PATHS bullet3/cmake-build-debug)

if(Bullet_FOUND)

#    message(STATUS "Found Bullet")
#    get_cmake_property(_variableNames VARIABLES)
#    list (SORT _variableNames)
#    foreach (_variableName ${_variableNames})
#        message(STATUS "${_variableName}=${${_variableName}}")
#    endforeach()

    include_directories(${Bullet_INCLUDE_DIRS})

    add_definitions     ( ${BULLET_DEFINITIONS} )
    include_directories ( ${BULLET_INCLUDE_DIRS} )
    #link_directories    ( ${BULLET_LIBRARY_DIRS} )

    link_directories(
            bullet3/cmake-build-debug/src/LinearMath
            bullet3/cmake-build-debug/src/Bullet3Common
            bullet3/cmake-build-debug/src/BulletInverseDynamics
            bullet3/cmake-build-debug/src/BulletCollision
            bullet3/cmake-build-debug/src/BulletDynamics
            bullet3/cmake-build-debug/src/BulletSoftBody
            bullet3/cmake-build-debug/lib
    )
    link_libraries(
            ${BULLET_LIBRARIES}
#            LinearMath
#            Bullet3Common
#            BulletInverseDynamics
#            BulletCollision
#            BulletDynamics
#            BulletSoftBody
    )
else()
    message(SEND_ERROR "Bullet is required for MetaEngine")
endif()

