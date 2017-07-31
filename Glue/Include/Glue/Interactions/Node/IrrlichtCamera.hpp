#pragma once

namespace Glue { namespace Irrlicht {
    class Component;
}}

namespace Glue { namespace Avatar {
    class Camera;
}}

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
