#pragma once

#include "Glue/Irrlicht/IrrlichtComponent.hpp"
#include "Glue/Avatar/AvatarComponent.hpp"

namespace Glue {

class IrrlichtKeyInput
{
private:
    Irrlicht::IrrlichtComponent* irrComp;
    Avatar::AvatarComponent* avComp;

public:
    IrrlichtKeyInput(
        Irrlicht::IrrlichtComponent* irrComp,
        Avatar::AvatarComponent* avComp
    );
    ~IrrlichtKeyInput();
};

}
