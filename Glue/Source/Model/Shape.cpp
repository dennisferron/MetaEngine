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

    void Shape::addAttribute(ShapeAttribute* attr)
    {
        // TODO: Run interactions on attr before adding to list
        attributes.push_back(attr);
    }

    std::vector<ShapeAttribute*> const& Shape::get_attributes() const
    {
        return attributes;
    }
}