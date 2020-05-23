#pragma once

#include "Glue/Styles/ShapeStyle.hpp"
#include "btBulletCollisionCommon.h"
#include "btRigidBody.h"

namespace Glue::Bullet
{
    btCollisionShape* create_physics_shape(ShapeStyle const& style, irr::scene::IMesh* dispShapeMesh);
    btTransform get_shape_transform(ShapeStyle const& style);
}
