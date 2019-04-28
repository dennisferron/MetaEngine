
add_subdirectory(bullet3)

include_directories(${Bullet_INCLUDE_DIRS})

#[[
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
            #bullet3/cmake-build-debug/lib
    )


link_libraries(
        LinearMath
        Bullet3Common
        BulletInverseDynamics
        BulletCollision
        BulletDynamics
        BulletSoftBody
)

]]