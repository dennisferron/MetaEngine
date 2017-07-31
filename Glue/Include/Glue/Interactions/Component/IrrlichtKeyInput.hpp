#pragma once

namespace Glue { namespace Irrlicht {
    Component;
}}

namespace Glue { namespace Avatar {
    Component;
}}

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
