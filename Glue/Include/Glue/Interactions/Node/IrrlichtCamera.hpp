#pragma once

#include "Glue/Irrlicht/Component.hpp"
#include "Glue/Avatar/Camera.hpp"
#include "Glue/Model/Time.hpp"

namespace Glue {

class IrrlichtCamera
{
private:
    Irrlicht::Component* irrComp;
    Time* time;
    Avatar::Camera* avatarCamera;

public:
    IrrlichtCamera(Irrlicht::Component* irrComp, Time* time, Avatar::Camera* avatarCamera);
    void enter();
};

}
