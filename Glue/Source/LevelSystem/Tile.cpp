// Copyright 2008-2013, 2018 Dennis Ferron

#include "Glue/LevelSystem/Tile.hpp"
#include "irrlicht.h"
#include "Glue/MeshTools/MeshTools.hpp"

using namespace std;
using namespace boost;

using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

namespace Glue {

Tile& Tile::refresh()
{
    Scalar tolerance = 0.05;

    auto splitForWalkway = MeshTools::createHillMesh(surface, tileRect, pathMinZ-tolerance, pathMaxZ+tolerance);

    struct TileStyle : GameObjStyle
    {
        TileStyle() : GameObjStyle(ObjShapes::none)
        {
            setGameObjType("static");
            setDispShape("mesh");
            setMass(0);
            setPos(0, 0, 0);
            setIsMouseDraggable(false);

            // For debugging
            //setWireframe(true);
        }
    };

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
        vector3df(-tileRect.getWidth/2.0f, walkwayDepth/2.0f, (walkwayDepth/2.0f)/repeatAmt)  // offset
    );

    auto walkStyle = TileStyle()
            .setTexture("Media/boardwalk.png")
            .setPhysShape("mesh")
            .setMesh(splitForWalkway);

    setWalkwayGameObj(graph->addNode(walkStyle));
    walkwayGameObj->addAttribute(self);

    repeatAmt = 1.0f/2.0f;

    s = repeatAmt / tileRect.getWidth();
    t = repeatAmt / tileRect.getHeight();

    splitBackFromSky = MeshTools::createHillMesh(surface, tileRect, skyCutZ-tolerance, pathMinZ+tolerance)

    meshMan makePlanarTextureMapping(
        splitBackFromSky getMeshBuffer(0),    // buffer
        s,  // resolutionS
        t,  // resolutionT
        2,  // axis
        vector3df(0, 0, 0)  // offset
    )

    backStyle = TileStyle()
            .setTexture("Media/mountaintop.jpg")
            .setMesh(splitBackFromSky)
            .setPhysShape("none");

    setBackGameObj(graph->addNode(backStyle))
    backGameObj->addAttribute(self)

    splitFront = MeshTools::createHillMesh(surface, tileRect, pathMaxZ-tolerance, 1000000);

    meshMan->makePlanarTextureMapping(
        splitFront getMeshBuffer(0),    // buffer
        s,  // resolutionS
        t,  // resolutionT
        2,  // axis
        vector3df(0, 0, 0)  // offset
    )

    foreStyle = TileStyle()
            .setTexture("Media/irrlicht2_dn.jpg")
            .setMesh(splitFront)
            .setPhysShape("none");

    setForeGameObj(graph->addNode(foreStyle));
    foreGameObj->addAttribute(self)

    return *this;
}

}
