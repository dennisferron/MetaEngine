#pragma once

namespace irr {

    namespace core {
        template <typename T>
        class bbox2d;

        typedef bbox2d<float> bbox2df;
    }

    namespace scene {
        class IMeshSceneNodeManager;
    }
}

namespace Glue {

using Scalar = double;

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
