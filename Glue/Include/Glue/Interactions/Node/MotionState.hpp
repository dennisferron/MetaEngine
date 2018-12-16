#pragma once

#include "Glue/Bullet/NodeAttribute.hpp"
#include "Glue/Irrlicht/NodeAttribute.hpp"

namespace Glue {

class MotionState
{
public:
    MotionState(Bullet::NodeAttribute* physRep, Irrlicht::NodeAttribute* dispRep);
};

}
