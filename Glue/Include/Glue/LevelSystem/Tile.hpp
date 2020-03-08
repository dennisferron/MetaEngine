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
    Graph* graph;
    irr::scene::IMeshManipulator* meshMan;

    irr::core::rectf tileRect;

    Scalar pathMinZ;
    Scalar pathMaxZ;
    Scalar skyCutZ;

    Node* backGameObj;
    Node* walkwayGameObj;
    Node* foreGameObj;

    SurfaceQuadTree* surface;

public:
    Tile& refresh();
};

}
