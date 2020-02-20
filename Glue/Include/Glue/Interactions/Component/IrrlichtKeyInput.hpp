#pragma once

#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"
#include "Glue/Avatar/AvatarInterfaces.hpp"

namespace Glue
{

class IrrlichtKeyInput
{
private:
    Irrlicht::IIrrlichtComponent* irrComp;
    Avatar::IAvatarComponent* avComp;

public:
    IrrlichtKeyInput(
        Irrlicht::IIrrlichtComponent* irrComp,
        Avatar::IAvatarComponent* avComp
    );
    ~IrrlichtKeyInput();
};

}
