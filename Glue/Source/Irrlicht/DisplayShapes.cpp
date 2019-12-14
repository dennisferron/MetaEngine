#include "Glue/Irrlicht/DisplayShapes.hpp"

#include <stdexcept>

using namespace irr::core;
using namespace irr::scene;

namespace Glue::Irrlicht {
    
    irr::scene::IMesh* DisplayShapes::create(GameObjStyle const& style) const
    {
        switch (style.dispShape)
        {
            case ObjShapes::none: return none(style);
            case ObjShapes::box: return box(style);
            case ObjShapes::ball: return ball(style);
            case ObjShapes::cyl: return cyl(style);
            case ObjShapes::cylX: return cylX(style);
            case ObjShapes::cylZ: return cylZ(style);
            case ObjShapes::cone: return cone(style);
            case ObjShapes::coneX: return coneX(style);
            case ObjShapes:: coneZ: return coneZ(style);
            case ObjShapes::skybox: return none(style);  // Handled by SceneNodeBuilder
            case ObjShapes::plane: return plane(style);
            case ObjShapes::mesh: return mesh(style);
            case ObjShapes::hills: return hills(style);
            default: throw std::logic_error("Unhandled dispShape");
        }
    }

    irr::scene::IMesh* DisplayShapes::none(GameObjStyle const& style) const
    {
        return nullptr;
    }

    irr::scene::IMesh* DisplayShapes::ball(GameObjStyle const& style) const
    {
        return geometry->createSphereMesh(
            style.radius, // radius
            16, // polyCountX
            16 // polyCountY
        );
    }

    irr::scene::IMesh* DisplayShapes::box(GameObjStyle const& style) const
    {
        return geometry->createCubeMesh(
            vector3df(style.xSize, style.ySize, style.zSize)
        );
    }

    irr::scene::IMesh* DisplayShapes::cyl(GameObjStyle const& style) const
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

    irr::scene::IMesh* DisplayShapes::cylX(GameObjStyle const& style) const
    {
        // Note: it is the shape offset with Bullet that
        // rotates the mesh to be a cylX or cylZ.
        return cyl(style);
    }

    irr::scene::IMesh* DisplayShapes::cylZ(GameObjStyle const& style) const
    {
        // Note: it is the shape offset with Bullet that
        // rotates the mesh to be a cylX or cylZ.
        return cyl(style);
    }

    irr::scene::IMesh* DisplayShapes::cone(GameObjStyle const& style) const
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

    irr::scene::IMesh* DisplayShapes::coneX(GameObjStyle const& style) const
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

    irr::scene::IMesh* DisplayShapes::coneZ(GameObjStyle const& style) const
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

    irr::scene::IMesh* DisplayShapes::hills(GameObjStyle const& style) const
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

    irr::scene::IMesh* DisplayShapes::plane(GameObjStyle const& style) const
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

    irr::scene::IMesh* DisplayShapes::cloth(GameObjStyle const& style) const
    {
        auto mesh = plane(style);
        mesh->setHardwareMappingHint(EHM_STREAM, EBT_VERTEX);
        auto buf = mesh->getMeshBuffer(0);
        buf->setHardwareMappingHint(EHM_STREAM, EBT_VERTEX);
        return mesh;
    }

    irr::scene::IMesh* DisplayShapes::mesh(GameObjStyle const& style) const
    {
        // TODO:  Find a way to pass in the mesh without putting an Irrlicht object into a generic style.
        if (!style.mesh)
            throw std::runtime_error("Style display shape is 'mesh' but style mesh slot is nil.");

        return style.mesh;
    }
}
