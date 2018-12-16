#pragma once

#include "IMeshManipulator.h"
#include "IMesh.h"
#include "rect.h"

#include "Glue/Constants.hpp"
#include "Glue/Model/Graph.hpp"

namespace Glue {

class Tile
{
private:
    Graph* graph;
    irr::scene::IMeshManipulator* meshMan;

    irr::core::rectf tileRect;

    Scalar pathMinZ;
    Scalar pathMaxZ;
    Scalar skyCutZ;

    Node* backGameObj;
    Node* walkwayGameObj;
    Node* foreGameObj;

    IMesh* surface;

public:
    Tile& refresh();
};

}
