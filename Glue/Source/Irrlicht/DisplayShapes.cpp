#include "Glue/Irrlicht/DisplayShapes.hpp"

#include <stdexcept>

using namespace irr::core;
using namespace irr::scene;
using namespace Glue;

namespace
{
    irr::scene::IMesh* create_hills(GameObjStyle const& style, irr::scene::IGeometryCreator const* geometry)
    {
        auto xSize = style.xSize / style.xTiles;
        auto zSize = style.zSize / style.zTiles;
        auto tileSize = dimension2df(xSize, zSize);
        auto tileCount = dimension2du(style.xTiles, style.zTiles);
        auto material = nullptr;
        auto hillHeight = style.ySize;
        auto countHills = dimension2df(style.xHills, style.zHills);
        auto textureRepeatCount = dimension2df(style.xTextureRepeat, style.zTextureRepeat);

        return geometry->createHillPlaneMesh(
                tileSize,
                tileCount,
                material,
                hillHeight,
                countHills,
                textureRepeatCount
        );
    }

    irr::scene::IMesh* create_plane(GameObjStyle const& style, irr::scene::IGeometryCreator const* geometry)
    {
        auto xSize = style.xSize / style.xTiles;
        auto zSize = style.zSize / style.zTiles;
        auto tileSize = dimension2df(xSize, zSize);
        auto tileCount = dimension2du(style.xTiles, style.zTiles);
        auto material = nullptr;
        auto textureRepeatCount = dimension2df(style.xTextureRepeat, style.zTextureRepeat);

        return geometry->createPlaneMesh(
                tileSize,
                tileCount,
                material,
                textureRepeatCount
        );
    }

    irr::scene::IMesh* create_cloth(GameObjStyle const& style, irr::scene::IGeometryCreator const* geometry)
    {
        auto mesh = create_plane(style, geometry);
        mesh->setHardwareMappingHint(EHM_STREAM, EBT_VERTEX);
        auto buf = mesh->getMeshBuffer(0);
        buf->setHardwareMappingHint(EHM_STREAM, EBT_VERTEX);
        return mesh;
    }

    irr::scene::IMesh* create_mesh(GameObjStyle const& style)
    {
        // TODO:  Find a way to pass in the mesh without putting an Irrlicht object into a generic style.
        if (!style.mesh)
            throw std::runtime_error("Style display shape is 'mesh' but style mesh slot is null.");

        return style.mesh;
    }

    // Note: it is the shape offset with Bullet that
    // rotates the mesh to be a cylX or cylZ.
    irr::scene::IMesh* create_cylinder(GameObjStyle const& style, irr::scene::IGeometryCreator const* geometry)
    {
        return geometry->createCylinderMesh(
                style.radius, // radius
                style.length, // length
                16, // tessellation (number of quads around)
                style.color, // color
                style.closeEnds, // closeTop
                0 // oblique (undocumented)
        );
    }

    // Note: it is the shape offset with Bullet that
    // rotates the mesh to be a cylX or cylZ.
    irr::scene::IMesh* create_cone(GameObjStyle const& style, irr::scene::IGeometryCreator const* geometry)
    {
        return geometry->createConeMesh(
                style.radius, // radius
                style.length, // length
                16, // tessellation (number of quads around)
                style.color, // colorTop
                style.color, // colorBottom
                0 // oblique (undocumented)
        );
    }

    irr::scene::IMesh* create_box(GameObjStyle const& style, irr::scene::IGeometryCreator const* geometry)
    {
        return geometry->createCubeMesh(
                vector3df(style.xSize, style.ySize, style.zSize)
        );
    }

    irr::scene::IMesh* create_ball(GameObjStyle const& style, irr::scene::IGeometryCreator const* geometry)
    {
        return geometry->createSphereMesh(
                style.radius, // radius
                16, // polyCountX
                16 // polyCountY
        );
    }
}

namespace Glue::Irrlicht {
    
    irr::scene::IMesh* create_display_shape(GameObjStyle const& style, irr::scene::IGeometryCreator const* geometry)
    {
        switch (style.dispShape)
        {
            case ObjShapes::none: return nullptr;
            case ObjShapes::box: return create_box(style, geometry);
            case ObjShapes::ball: return create_ball(style, geometry);
            case ObjShapes::cyl: return create_cylinder(style, geometry);
            case ObjShapes::cylX: return create_cylinder(style, geometry);
            case ObjShapes::cylZ: return create_cylinder(style, geometry);
            case ObjShapes::cone: return create_cone(style, geometry);
            case ObjShapes::coneX: return create_cone(style, geometry);
            case ObjShapes:: coneZ: return create_cone(style, geometry);
            case ObjShapes::plane: return create_plane(style, geometry);
            case ObjShapes::mesh: return create_mesh(style);
            case ObjShapes::hills: return create_hills(style, geometry);
            //case ObjShapes::skybox:  throw std::logic_error("Skybox should be handled by SceneNodeBuilder");
            default: throw std::logic_error("Unhandled dispShape");
        }
    }
}
