#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "btRigidBody.h"
#include "btBulletCollisionCommon.h"

namespace Glue::Bullet
{

class ShapeBuilder
{
public:
    btCollisionShape* create(NodeStyle const& style, irr::scene::IMesh* dispShapeMesh) const;
    btTransform getOffset(NodeStyle const& style) const;
};

}
