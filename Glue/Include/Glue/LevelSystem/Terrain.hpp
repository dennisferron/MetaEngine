#pragma once

#include "irrlicht.h"

#include "Glue/MeshTools/MeshTools.hpp"
#include "Glue/MeshTools/SurfaceQuadTree.hpp"
#include "Glue/Constants.hpp"

#include "Glue/Model/Graph.hpp"
#include "Glue/LevelSystem/Tile.hpp"

#include <vector>

namespace Glue {

class Terrain
{
private:
    Graph* graph;
    irr::scene::IMeshManipulator* meshMan;

    irr::core::rectf levelRect;
    irr::core::dimension2df tileDimensions;

    std::vector<Tile*> tileArray;
    int numTilesX;
    int numTilesY;

    TPS::ThinPlateQuilt* tps;
    SurfaceQuadTree* surface;

    int initialSplit = 4;

    Scalar pathMinZ = -2.0;
    Scalar pathMaxZ = 2.0;
    Scalar skyCutZ = -9.0;

    Scalar minFitSizeLen = 0.5 + 0.01;

    irr::core::dimension2df minFitSize = irr::core::dimension2df(minFitSizeLen, minFitSizeLen);

public:
    Terrain();
    void load();
    std::size_t tileIndex(int x, int y) const;
};

}
