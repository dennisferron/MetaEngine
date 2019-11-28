#pragma once

#include "Glue/Model/TimeComponent.hpp"
#include "Glue/Bullet/BulletComponent.hpp"

namespace Glue {

class BulletTime
{
private:
    Bullet::BulletComponent* bltComp;
    TimeComponent* time;

public:
    BulletTime(
            Bullet::BulletComponent* bltComp,
            TimeComponent* time
    );
    ~BulletTime();
};

}
