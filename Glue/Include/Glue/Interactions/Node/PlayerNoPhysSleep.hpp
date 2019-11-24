#pragma once

#include "Glue/Bullet/BulletAttribute.hpp"
#include "Glue/Avatar/AvatarAttribute.hpp"

namespace Glue {

class PlayerNoPhysSleep
{
public:
    PlayerNoPhysSleep(Bullet::BulletAttribute* physRep, Avatar::AvatarAttribute* playerRep);
};

}
