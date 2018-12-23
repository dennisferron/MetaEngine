#pragma once

#include <functional>
#include <memory>

#include "Glue/Constants.hpp"

namespace Glue {
    class Node;
}

namespace Glue { namespace Desteer {

class Steering
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    Steering();
    ~Steering();

    Steering& addObstacleGameObj(Node* gameObj);
    Steering& setHideTarget(Node* otherSteering);
    Steering& setPursuitTarget(Node* otherSteering);

    void update(Scalar timeElapsed);
};

}}
