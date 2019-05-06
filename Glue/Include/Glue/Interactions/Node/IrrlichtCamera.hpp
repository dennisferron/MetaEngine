#pragma once

#include "Glue/Irrlicht/IrrlichtComponent.hpp"
#include "Glue/Avatar/Camera.hpp"
#include "Glue/Model/Time.hpp"

namespace Glue {

class IrrlichtCamera
{
private:
    Irrlicht::IrrlichtComponent* irrComp;
    Time* time;
    Avatar::Camera* avatarCamera;

public:
    IrrlichtCamera(Irrlicht::IrrlichtComponent* irrComp, Time* time, Avatar::Camera* avatarCamera);
    void enter();
};

}
