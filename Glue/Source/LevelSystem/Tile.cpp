// Copyright 2008-2013, 2018 Dennis Ferron

#include "Glue/Tile.hpp"
#include "irrlicht.h"

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

    auto tileStyle = EmptyStyle()
        .setGameObjType("static")
        .setDispShape("mesh")
        .setMass(0)
        .setPos(0, 0, 0)
        .setIsMouseDraggable(false);

    // For debugging
    //tileStyle setWireframe(true)

    // Temporary
    walkwayDepth := 4.0
    repeatAmt := 1.0 / 2.0
    s := repeatAmt/walkwayDepth
    t := repeatAmt/walkwayDepth

    meshMan makePlanarTextureMapping(
        splitForWalkway getMeshBuffer(0),    // buffer
        s,  // resolutionS
        t,  // resolutionT
        1,  // axis
        vector3df tmp(-tileRect getWidth/2.0, walkwayDepth/2.0, (walkwayDepth/2.0)/repeatAmt)  // offset
    )

    walkStyle := tileStyle clone setTexture("Media/boardwalk.png") setPhysShape("mesh") setMesh(splitForWalkway)
    setWalkwayGameObj(graph addNode(walkStyle))
    walkwayGameObj addAttribute(self)

    repeatAmt := 1.0/2.0

    s := repeatAmt / tileRect getWidth
    t := repeatAmt / tileRect getHeight

    splitBackFromSky := MeshTools createHillMesh(surface, tileRect, skyCutZ-tolerance, pathMinZ+tolerance)

    meshMan makePlanarTextureMapping(
        splitBackFromSky getMeshBuffer(0),    // buffer
        s,  // resolutionS
        t,  // resolutionT
        2,  // axis
        vector3df tmp(0, 0, 0)  // offset
    )

    backStyle := tileStyle clone setTexture("Media/mountaintop.jpg") setMesh(splitBackFromSky) setPhysShape("none")
    setBackGameObj(graph addNode(backStyle))
    backGameObj addAttribute(self)

    splitFront := MeshTools createHillMesh(surface, tileRect, pathMaxZ-tolerance, 1000000)

    meshMan makePlanarTextureMapping(
        splitFront getMeshBuffer(0),    // buffer
        s,  // resolutionS
        t,  // resolutionT
        2,  // axis
        vector3df tmp(0, 0, 0)  // offset
    )

    foreStyle := tileStyle clone setTexture("Media/irrlicht2_dn.jpg") setMesh(splitFront) setPhysShape("none")
    setForeGameObj(graph addNode(foreStyle))
    foreGameObj addAttribute(self)

    return *this;
}

}
