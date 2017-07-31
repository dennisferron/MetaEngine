#pragma once

namespace Glue { namespace Bullet {
    class Component;
}}

namespace Glue { namespace Irrlicht {
    class Component;
}}

namespace Glue {

class DebugDrawer
{
private:
    Bullet::Component* physComp;
    Irrlicht::Component* dispComp;

public:
    DebugDrawer(
        Bullet::Component* physComp,
        Irrlicht::Component* dispComp
    );
};

}
