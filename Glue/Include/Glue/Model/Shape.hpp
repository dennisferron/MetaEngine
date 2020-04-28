#include "Glue/Styles/ShapeStyle.hpp"

namespace irr::video
{
    class ITexture;
}

namespace irr::scene
{
    class IMesh;
}

class btCollisionShape;

namespace Glue
{
    class ShapeAttribute;

    struct Shape
    {
        btCollisionShape* collision_shape;
        irr::scene::IMesh* dispShape;
        btTransform transform;
    };
}
