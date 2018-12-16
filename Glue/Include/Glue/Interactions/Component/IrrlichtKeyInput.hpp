#pragma once

#include "Glue/Irrlicht/Component.hpp"
#include "Glue/Avatar/Component.hpp"

namespace Glue {

class IrrlichtKeyInput
{
private:
    Irrlicht::Component* irrComp;
    Avatar::Component* avComp;

public:
    IrrlichtKeyInput(
        Irrlicht::Component* irrComp,
        Avatar::Component* avComp
    );
    ~IrrlichtKeyInput();
};

}
