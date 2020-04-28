#include "Glue/Factory/ShapeFactory.hpp"

namespace Glue
{
    ShapeFactory::ShapeFactory(irr::scene::IGeometryCreator* geometry)
            : geometry(geometry)
    {
    }

    void ShapeFactory::changeTextureWrap(irr::scene::IMesh* mesh) const
    {
        auto buf = mesh->getMeshBuffer(0);

        if (buf->getVertexCount() == 0)
            return;

        auto pos = buf->getPosition(0);
        float minX = pos.X;
        float maxX = pos.X;
        float minZ = pos.Z;
        float maxZ = pos.Z;

        // Find the extents so we can scale our texture coords to 0..1
        for(int i=1; i < buf->getVertexCount(); i++)
        {
            pos = buf->getPosition(i);
            if (pos.X < minX) minX = pos.X;
            if (pos.Z < minZ) minZ = pos.Z;
            if (pos.X > maxX) maxX = pos.X;
            if (pos.Z > maxZ) maxZ = pos.Z;
        }

        auto scaleX = 1.0/(maxX - minX);
        auto scaleZ = 1.0/(maxZ - minZ);

        for(int i=0; i < buf->getVertexCount(); i++)
        {
            pos = buf->getPosition(i);
            auto tcoords = buf->getTCoords(i);
            tcoords.X = (float)( (pos.X - minX) * scaleX );
            tcoords.Y = (float)( (pos.Z - minZ) * scaleZ );
        }

        buf->setDirty(EBT_VERTEX);
    }

    Shape* ShapeFactory::createShape(ShapeStyle const& style) const
    {
        irr::scene::IMesh* dispShape = create_display_shape(style, geometry);

        if (dispShape != nullptr && style.alternateTextureWrap == true)
            changeTextureWrap(dispShape);

        if (dispShape != nullptr && style.onTextureWrap != nullptr)
            style.onTextureWrap(dispShape);

        auto physShape = create_physics_shape(style, dispShapeMesh);

        if (physShape != nullptr && style.margin)
            physShape->setMargin(*style.margin);

        btTransform transform = get_shape_transform()

        return new Shape { dispShape, physShape, transform };
    }

    btTransform ShapeFactory::get_shape_transform(ShapeStyle const& style)
    {
        constexpr btScalar TAU = 6.28318530718;

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