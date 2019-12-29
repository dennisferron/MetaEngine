#include "Glue/Bullet/ShapeOffsets.hpp"

#include "Glue/Constants.hpp"

using namespace Glue::Constants;

namespace Glue::Bullet {

    btTransform get_shape_transform(NodeStyle const &style)
    {
        switch (style.physShape)
        {
            case ObjShapes::none:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::ball:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::box:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::cyl:
            {
                auto axis = btVector3(0, 1, 0);
                float angle = 0;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(0, -style.length / 2, 0);

                return btTransform(q, v);
            }
            case ObjShapes::cylX:
            {
                auto axis = btVector3(0, 0, 1);
                auto angle = TAU / 4;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(style.length / 2, 0, 0);

                return btTransform(q, v);
            }
            case ObjShapes::cylZ:
            {
                auto axis = btVector3(1, 0, 0);
                auto angle = TAU / 4;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(0, 0, -style.length / 2);

                return btTransform(q, v);
            }
            case ObjShapes::cone:
            {
                auto axis = btVector3(0, 0, 1);
                auto angle = 0;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(0, -style.length / 2, 0);

                return btTransform(q, v);
            }
            case ObjShapes::coneX:
            {
                auto axis = btVector3(0, 0, 1);
                auto angle = -TAU / 4;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(-style.length / 2, 0, 0);

                return btTransform(q, v);
            }
            case ObjShapes::coneZ:
            {
                auto axis = btVector3(1, 0, 0);
                auto angle = TAU / 4;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(0, 0, -style.length / 2);
                //auto v = btVector3(0, 0, 0);

                return btTransform(q, v);
            }
            case ObjShapes::hills:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::mesh:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::plane:
            {
                return btTransform::getIdentity();
            }
            default:
            {
                throw std::logic_error("Unknown ObjShape");
            }
        }
    }
}

