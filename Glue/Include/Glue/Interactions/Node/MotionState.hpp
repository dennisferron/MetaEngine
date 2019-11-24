#pragma once

#include "Glue/Bullet/BulletAttribute.hpp"
#include "Glue/Irrlicht/IrrlichtAttribute.hpp"

namespace Glue {

class MotionState
{
public:
    MotionState(Bullet::BulletAttribute* physRep, Irrlicht::IrrlichtAttribute* dispRep);
};

}
