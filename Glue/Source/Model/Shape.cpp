#include "Glue/Model/Shape.hpp"

#include "Glue/Utility/variant_helpers.hpp"

namespace Glue
{
    Shape::Shape(ShapeStyle const& style)
        : style(style)
    {
    }

    ShapeStyle const& Shape::get_style() const
    {
        return style;
    }

    void Shape::addAttribute(ShapeAttribute attr)
    {
        // TODO: Run interactions on attr before adding to list
        attributes.push_back(attr);
    }

    Irrlicht::IIrrlichtShape* Shape::get_irrlicht_shape() const
    {
        return find_attribute<Irrlicht::IIrrlichtShape>(attributes);
    }

    Bullet::IBulletShape* Shape::get_bullet_shape() const
    {
        return find_attribute<Bullet::IBulletShape>(attributes);
    }
}