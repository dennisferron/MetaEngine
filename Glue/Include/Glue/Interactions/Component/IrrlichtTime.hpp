#pragma once

#include "Glue/Model/Time.hpp"
#include "Glue/Irrlicht/IrrlichtComponent.hpp"

namespace Glue {

class IrrlichtTime
{
private:
    Irrlicht::IrrlichtComponent* irrComp;
    Time* time;

public:
    IrrlichtTime(
        Irrlicht::IrrlichtComponent* irrComp,
        Time* time
    );
    ~IrrlichtTime();
};

}
