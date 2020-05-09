#pragma once

#include "Glue/Model/Shape.hpp"
#include "Glue/Styles/ShapeStyle.hpp"

namespace Glue
{
    class ShapeFactory
    {
    private:
        irr::scene::IGeometryCreator const* geometry;

        void changeTextureWrap(irr::scene::IMesh* mesh) const;

    public:
        ShapeFactory(irr::scene::IGeometryCreator const* geometry);
        Shape* createShape(ShapeStyle const& style) const;
    };
}
