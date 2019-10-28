#pragma once

#include "Glue/Styles/GameObjStyle.hpp"

class btRigidBody;
class btTransform;

namespace Glue { namespace Bullet {
    class PhysicsShapes;
    class ShapeOffsets;
}}

namespace Glue { namespace Bullet {

class ShapeBuilder
{
private:
    PhysicsShapes* physicsShapes;
    ShapeOffsets* shapeOffsets;

public:
    ShapeBuilder(
        PhysicsShapes* physicsShapes,
        ShapeOffsets* shapeOffsets
    );

    btRigidBody create(NodeStyle style) const;
    btTransform getOffset(NodeStyle style) const;
};

}}
