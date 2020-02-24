#include "Glue/Bullet/BulletShape.hpp"

namespace Glue::Bullet
{
    BulletShape::BulletShape(btCollisionShape* collision_shape)
        : collision_shape(collision_shape)
    {
    }

    btCollisionShape* BulletShape::get_collision_shape() const
    {
        return collision_shape;
    }
}