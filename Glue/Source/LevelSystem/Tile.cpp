// Copyright 2008-2013, 2018 Dennis Ferron

#include "Glue/LevelSystem/Tile.hpp"
#include "irrlicht.h"
#include "Glue/MeshTools/MeshTools.hpp"
#include "Glue/Styles/GameObjStyles.hpp"

using namespace std;
using namespace boost;

using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

namespace
{
    using namespace Glue;
    using namespace Glue::GameObjStyles;

    GameObjStyle TileStyle()
    {
        GameObjStyle result = HillStyle();

        result.physShape = ObjShapes::mesh;
        result.dispShape = ObjShapes::mesh;
        result.gameObjType = GameObjTypes::static_;
        result.mass = 0;
        result.setPos(0, 0, 0);

        // Since it's static it's already not mouseDraggable
        //setIsMouseDraggable(false);

        // For debugging
        //setWireframe(true);

        return result;
    }

    GameObjStyle WalkStyle()
    {
        return TileStyle();
    }
}

namespace Glue {

Tile& Tile::refresh()
{
    Scalar tolerance = 0.05;

    throw "TODO: move surface to a constructor parameter so that it cannot be null here.";

/*
    auto splitForWalkway = MeshTools::createHillMesh(*surface, tileRect, pathMinZ-tolerance, pathMaxZ+tolerance);

    // Temporary
    float walkwayDepth = 4.0f;
    float repeatAmt = 1.0f / 2.0f;
    float s = repeatAmt/walkwayDepth;
    float t = repeatAmt/walkwayDepth;

    meshMan->makePlanarTextureMapping(
        splitForWalkway->getMeshBuffer(0),    // buffer
        s,  // resolutionS
        t,  // resolutionT
        1,  // axis
        vector3df(-tileRect.getWidth()/2.0f, walkwayDepth/2.0f, (walkwayDepth/2.0f)/repeatAmt)  // offset
    );

    auto walkStyle = WalkStyle();

    walkStyle.setTextureFile("Media/boardwalk.png");
            //.setPhysShape("mesh")
            //.setMesh(splitForWalkway);
    walkStyle.physShape = ObjShapes::mesh;
    walkStyle.mesh = splitForWalkway;

    walkwayGameObj = graph->addNode(walkStyle);

    throw "Need to be able to add Tile as a node attribute of walkwayGameObj";
    //walkwayGameObj->addAttribute(this);

    repeatAmt = 1.0f/2.0f;

    s = repeatAmt / tileRect.getWidth();
    t = repeatAmt / tileRect.getHeight();

    auto splitBackFromSky = MeshTools::createHillMesh(*surface, tileRect, skyCutZ-tolerance, pathMinZ+tolerance);

    meshMan->makePlanarTextureMapping(
        splitBackFromSky->getMeshBuffer(0),    // buffer
        s,  // resolutionS
        t,  // resolutionT
        2,  // axis
        vector3df(0, 0, 0)  // offset
    );

    auto backStyle = TileStyle();
            //.setTexture("Media/mountaintop.jpg")
            //.setMesh(splitBackFromSky)
            //.setPhysShape("none");

    backStyle.textureFile = "Media/mountaintop.jpg";
    backStyle.mesh = splitBackFromSky;
    backStyle.physShape = ObjShapes::none;

    backGameObj = graph->addNode(backStyle);

    throw "Need to be able to add Tile as a node attribute";
    //backGameObj->addAttribute(self)

    auto splitFront = MeshTools::createHillMesh(*surface, tileRect, pathMaxZ-tolerance, 1000000);

    meshMan->makePlanarTextureMapping(
        splitFront->getMeshBuffer(0),    // buffer
        s,  // resolutionS
        t,  // resolutionT
        2,  // axis
        vector3df(0, 0, 0)  // offset
    );

    auto foreStyle = TileStyle();
    foreStyle.textureFile = "Media/irrlicht2_dn.jpg";
    foreStyle.mesh = splitFront;
    foreStyle.physShape = ObjShapes::none;

    foreGameObj = graph->addNode(foreStyle);

    throw "Need to be able to add Tile as a node attribute";
    //foreGameObj->addAttribute(self);

    return *this;
*/
}

}
