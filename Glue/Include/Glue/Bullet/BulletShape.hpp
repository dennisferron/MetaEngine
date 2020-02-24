#pragma once

#include "Glue/Bullet/BulletInterfaces.hpp"

namespace Glue::Bullet
{
    class BulletShape : public IBulletShape
    {
    private:
        btCollisionShape* collision_shape;

    public:
        BulletShape(btCollisionShape* collision_shape);
        btCollisionShape* get_collision_shape() const final;
    };
}