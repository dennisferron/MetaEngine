#pragma once

#include "irrlicht.h"

namespace Glue {

class Tile
{
private:
    Graph* graph;
    irr::scene::IMeshSceneNodeManager;

    irr::core::bbox2df tileRect;

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
