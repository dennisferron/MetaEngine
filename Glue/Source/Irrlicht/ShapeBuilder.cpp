#include "Glue/Irrlicht/ShapeBuilder.hpp"

using namespace irr::scene;

namespace Glue::Irrlicht {

    void ShapeBuilder::changeTextureWrap(irr::scene::IMesh* mesh) const
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

    ShapeBuilder::ShapeBuilder(irr::scene::IGeometryCreator* geometry)
        : geometry(geometry)
    {
    }
    
    irr::scene::IMesh* ShapeBuilder::create(GameObjStyle const& style) const
    {
        auto dispShape = create_display_shape(style, geometry);

        if (dispShape != nullptr && style.alternateTextureWrap == true)
            changeTextureWrap(dispShape);

        if (dispShape != nullptr && style.onTextureWrap != nullptr)
            style.onTextureWrap(dispShape);

        return dispShape;
    }
}