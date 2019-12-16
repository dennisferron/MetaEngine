#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "btRigidBody.h"
#include "btBulletCollisionCommon.h"

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

    btCollisionShape* create(NodeStyle style) const;
    btTransform getOffset(NodeStyle style) const;
};

}}
