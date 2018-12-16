#pragma once

#include "Glue/Model/Time.hpp"
#include "Glue/Bullet/Component.hpp"

namespace Glue {

class BulletTime
{
private:
    Bullet::Component* bltComp;
    Time* time;

public:
    BulletTime(
        Bullet::Component* bltComp,
        Time* time
    );
    ~BulletTime();
};

}
