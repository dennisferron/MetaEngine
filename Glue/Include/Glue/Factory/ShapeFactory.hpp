#pragma once

namespace Glue
{
    class ShapeFactory
    {
    private:
        irr::scene::IGeometryCreator* geometry;

        void changeTextureWrap(irr::scene::IMesh* mesh) const;
        static btTransform get_shape_transform(ShapeStyle const& style);

    public:
        ShapeFactory(irr::scene::IGeometryCreator* geometry);

        Shape* createShape(ShapeStyle const& style) const;
    };
}
