#pragma once

#include "Glue/Model/TimeComponent.hpp"
#include "Glue/Irrlicht/IrrlichtComponent.hpp"

namespace Glue {

class IrrlichtTime
{
private:
    Irrlicht::IrrlichtComponent* irrComp;
    TimeComponent* time;

public:
    IrrlichtTime(
            Irrlicht::IrrlichtComponent* irrComp,
            TimeComponent* time
    );
    ~IrrlichtTime();
};

}
