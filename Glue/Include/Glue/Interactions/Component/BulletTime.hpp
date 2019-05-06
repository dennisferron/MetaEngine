#pragma once

#include "Glue/Model/Time.hpp"
#include "Glue/Bullet/BulletComponent.hpp"

namespace Glue {

class BulletTime
{
private:
    Bullet::BulletComponent* bltComp;
    Time* time;

public:
    BulletTime(
        Bullet::BulletComponent* bltComp,
        Time* time
    );
    ~BulletTime();
};

}
