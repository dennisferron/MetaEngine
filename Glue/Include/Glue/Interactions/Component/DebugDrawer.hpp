#pragma once

namespace Glue { namespace Bullet {
    class BulletComponent;
}}

namespace Glue { namespace Irrlicht {
    class IrrlichtComponent;
}}

namespace Glue {

class DebugDrawer
{
private:
    Bullet::BulletComponent* physComp;
    Irrlicht::IrrlichtComponent* dispComp;

public:
    DebugDrawer(
        Bullet::BulletComponent* physComp,
        Irrlicht::IrrlichtComponent* dispComp
    );
};

}
