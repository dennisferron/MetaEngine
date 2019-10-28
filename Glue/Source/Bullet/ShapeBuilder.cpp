#include "Glue/Bullet/ShapeBuilder.hpp"

#include "btRigidBody.h"

namespace Glue { namespace Bullet {

ShapeBuilder::ShapeBuilder(
        PhysicsShapes* physicsShapes,
        ShapeOffsets* shapeOffsets
)
    :   physicsShapes(physicsShapes),
        shapeOffsets(shapeOffsets)
{

}

btRigidBody ShapeBuilder::create(NodeStyle style) const
{
    throw "not implemented";
}

btTransform ShapeBuilder::getOffset(NodeStyle style) const
{
    throw "not implemented";
}

}}

/*
method(namespace_Bullet,
    ShapeBuilder := Object clone lexicalDo(
        appendProto(namespace_Bullet)

        physicsShapes ::= nil
        shapeOffsets ::= nil

        create := method(style,

            physShape := physicsShapes perform(style physShape, style, style mesh)

            if (physShape != nil and style margin != style default,
                physShape setMargin(style margin)
            )

            return physShape
        )

        getOffset := method(style,
            return shapeOffsets perform(style physShape, style)
        )
    )
)
*/
