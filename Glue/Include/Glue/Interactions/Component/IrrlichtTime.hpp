#pragma once

#include "Glue/Model/Time.hpp"
#include "Glue/Irrlicht/Component.hpp"

namespace Glue {

class IrrlichtTime
{
private:
    Irrlicht::Component* irrComp;
    Time* time;

public:
    IrrlichtTime(
        Irrlicht::Component* irrComp,
        Time* time
    );
    ~IrrlichtTime();
};

}
