#pragma once

#include "Glue/Bullet/NodeAttribute.hpp"
#include "Glue/Avatar/NodeAttribute.hpp"

namespace Glue {

class PlayerNoPhysSleep
{
public:
    PlayerNoPhysSleep(Bullet::NodeAttribute* physRep, Avatar::NodeAttribute* playerRep);
};

}
