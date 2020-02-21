#pragma once

#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"

namespace Glue
{

class IrrlichtTime
{
private:
    Irrlicht::IIrrlichtComponent* irrComp;
    ITimeComponent* time;

public:
    IrrlichtTime(
            Irrlicht::IIrrlichtComponent* irrComp,
            ITimeComponent* time
    );
    ~IrrlichtTime();
};

}
