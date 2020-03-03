#include "Glue/Model/ModelInterfaces.hpp"

namespace Glue
{
    class Shape : public IShape
    {
    private:
        ShapeStyle style;
        //ShapeInteractions interactions;
        std::vector<ShapeAttribute> attributes;

    public:
        Shape(ShapeStyle const& style);

        ShapeStyle const& get_style() const final;

        void addAttribute(ShapeAttribute* attr) final;

        Irrlicht::IIrrlichtShape* get_irrlicht_shape() const final;

        Bullet::IBulletShape* get_bullet_shape() const final;
    };
}
