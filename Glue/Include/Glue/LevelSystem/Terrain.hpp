#pragma once

#include "irrlicht.h"

#include "MeshTools.hpp"

#include <vector>

namespace Glue {

class Graph;
class Tile;

class Terrain
{
private:
    Graph* graph;
    irr::scene::IMeshSceneNodeManager* meshMan;

    irr::core::bbox2df levelRect;
    irr::core::dimension2df tileDimensions;

    std::vector<Tile*> tileArray;
    int numTilesX;
    int numTilesY;

    TPS::ThinPlateQuilt tps;
    SurfaceQuadTree surface;

    int initialSplit = 4;

    Scalar pathMinZ = -2.0;
    Scalar pathMaxZ = 2.0;
    Scalar skyCutZ = -9.0;

    Scalar minFitSizeLen = 0.5 + 0.01;

    irr::core::dimension2df minFitSize;

public:
    Terrain();
    void load();
    std::size_t tileIndex(int x, int y) const;
};

}
