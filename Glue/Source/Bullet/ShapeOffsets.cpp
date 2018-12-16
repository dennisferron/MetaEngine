#include "Glue/Bullet/ShapeOffsets.hpp"

namespace Glue { namespace Bullet {

    btTransform ShapeOffsets::none(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::ball(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::box(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::cyl(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::cylX(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::cylZ(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::cone(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::coneX(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::coneZ(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::hills(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::mesh(NodeStyle const& style) { throw "Not implemented"; }
    btTransform ShapeOffsets::cloth(NodeStyle const& style) { throw "Not implemented"; }

}}

/*
method(namespace_Bullet, Constants,
    ShapeOffsets := Object clone lexicalDo(
        appendProto(namespace_Bullet)
        appendProto(Constants)

        none := method(
            namespace_Bullet getIdentityTransform
        )

        ball := method(
            namespace_Bullet getIdentityTransform
        )

        box := method(
            namespace_Bullet getIdentityTransform
        )

        cyl := method(style,
            axis := btVector3 tmp(0, 1, 0)
            angle := 0
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(0, -style length/2, 0)

            btTransform tmp(q, v)
        )

        cylX := method(style,
            axis := btVector3 tmp(0, 0, 1)
            angle := TAU/4
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(style length/2, 0, 0)
            //v := btVector3 tmp(0, 0, 0)

            btTransform tmp(q, v)
        )

        cylZ := method(style,
            axis := btVector3 tmp(1, 0, 0)
            angle := TAU/4
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(0, 0, -style length/2)
            //v := btVector3 tmp(0, 0, 0)

            btTransform tmp(q, v)
        )

        cone := method(style,
            axis := btVector3 tmp(0, 0, 1)
            angle := 0
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(0, -style length/2, 0)

            btTransform tmp(q, v)
        )

        coneX := method(style,
            axis := btVector3 tmp(0, 0, 1)
            angle := -TAU/4
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(-style length/2, 0, 0)
            //v := btVector3 tmp(0, 0, 0)

            btTransform tmp(q, v)
        )

        coneZ := method(style,
            axis := btVector3 tmp(1, 0, 0)
            angle := TAU/4
            q := btQuaternion tmp(axis, angle)

            v := btVector3 tmp(0, 0, -style length/2)
            //v := btVector3 tmp(0, 0, 0)

            btTransform tmp(q, v)
        )

        hills := method(
            namespace_Bullet getIdentityTransform
        )

        mesh := method(
            namespace_Bullet getIdentityTransform
        )

        cloth := method(
            namespace_Bullet getIdentityTransform
        )
    )

    ShapeOffsets namespace_Bullet := namespace_Bullet

    return ShapeOffsets
)
*/
