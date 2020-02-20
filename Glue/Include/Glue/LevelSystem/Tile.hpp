#pragma once

#include "IMeshManipulator.h"
#include "IMesh.h"
#include "rect.h"

#include "Glue/Constants.hpp"
#include "Glue/Model/ModelInterfaces.hpp"

#include "Glue/MeshTools/SurfaceQuadTree.hpp"

namespace Glue {

class Tile
{
public:
    IGraph* graph;
    irr::scene::IMeshManipulator* meshMan;

    irr::core::rectf tileRect;

    Scalar pathMinZ;
    Scalar pathMaxZ;
    Scalar skyCutZ;

    INode* backGameObj;
    INode* walkwayGameObj;
    INode* foreGameObj;

    SurfaceQuadTree* surface;

public:
    Tile& refresh();
};

}
