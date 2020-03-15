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

    class Shape
    {
    private:
        btCollisionShape* collision_shape;
        irr::scene::IMesh* dispShape;
        irr::video::ITexture* texture;

    public:
        Shape(
            btCollisionShape* collision_shape,
            irr::scene::IMesh* dispShape,
            irr::video::ITexture* texture
            );
    };
}
