#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"

namespace Glue::Bullet
{
    btCollisionShape* create_physics_shape(GameObjStyle const& style, irr::scene::IMesh* dispShapeMesh);
}
