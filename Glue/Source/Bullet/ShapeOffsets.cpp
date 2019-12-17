#include "Glue/Bullet/ShapeOffsets.hpp"

namespace Glue { namespace Bullet {

        btTransform get_shape_transform(NodeStyle const& style) const
        {
            switch (style.physShape)
            {
                case ShapeOffsets::none:
                {
                    return btTransform::getIdentity();
                }
                case ShapeOffsets::ball:
                {
                    return btTransform::getIdentity();
                }
                case ShapeOffsets::box:
                {
                    return btTransform::getIdentity();
                }
                case ShapeOffsets::cyl:
                {
                    auto axis = btVector3(0, 1, 0);
                    float angle = 0;
                    auto q = btQuaternion(axis, angle);

                    auto v = btVector3(0, -style length/2, 0);

                    return btTransform(q, v);
                }
                case ShapeOffsets::cylX:
                {
                    auto axis = btVector3(0, 0, 1);
                    auto angle = TAU/4;
                    auto q = btQuaternion(axis, angle);

                    auto v = btVector3(style.length/2, 0, 0);

                    return btTransform(q, v);
                }
                case ShapeOffsets::cylZ:
                {
                    auto axis = btVector3(1, 0, 0);
                    auto angle = TAU/4;
                    auto q = btQuaternion(axis, angle);

                    auto v = btVector3(0, 0, -style.length/2);

                    return btTransform(q, v);
                }
                case ShapeOffsets::cone:
                {
                    auto axis = btVector3(0, 0, 1);
                    auto angle = 0;
                    auto q = btQuaternion(axis, angle);

                    auto v = btVector3(0, -style length/2, 0);

                    return btTransform(q, v);
                }
                case ShapeOffsets::coneX:
                {
                    auto axis = btVector3(0, 0, 1);
                    auto angle = -TAU/4
                    auto q = btQuaternion(axis, angle);

                    auto v = btVector3(-style length/2, 0, 0);

                    return btTransform(q, v);
                }
                case ShapeOffsets::coneZ:
                {
                    auto axis = btVector3(1, 0, 0);
                    auto angle = TAU/4
                    auto q = btQuaternion(axis, angle);

                    auto v = btVector3(0, 0, -style length/2);
                    //auto v = btVector3(0, 0, 0);

                    return btTransform(q, v);
                }
                case ShapeOffsets::hills:
                {
                    return btTransform::getIdentity();
                }
                case ShapeOffsets::mesh:
                {
                    return btTransform::getIdentity();
                }
                case ShapeOffsets::cloth:
                {
                    return btTransform::getIdentity();
                }
            }
        }

 
}}

