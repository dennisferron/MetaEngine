#pragma once

#include "Glue/Irrlicht/IrrlichtComponent.hpp"
#include "Glue/Avatar/Camera.hpp"
#include "Glue/Model/TimeComponent.hpp"

namespace Glue {

class IrrlichtCamera
{
private:
    Irrlicht::IrrlichtComponent* irrComp;
    TimeComponent* time;
    Avatar::Camera* avatarCamera;

public:
    IrrlichtCamera(Irrlicht::IrrlichtComponent* irrComp, TimeComponent* time, Avatar::Camera* avatarCamera);
    void enter();
};

}
