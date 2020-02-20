#pragma once

#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Model/TimeComponent.hpp"
#include "Glue/Bullet/BulletInterfaces.hpp"

namespace Glue
{

    class BulletTime
    {
    private:
        Bullet::IBulletComponent* bltComp;
        TimeComponent* time;

    public:
        BulletTime(
                Bullet::IBulletComponent* bltComp,
                TimeComponent* time
        );

        ~BulletTime();
    };

}
