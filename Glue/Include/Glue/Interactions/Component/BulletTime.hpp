#pragma once

namespace Glue {
    class Time;
}

namespace Glue { namespace Bullet {
    Component;
}}

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
