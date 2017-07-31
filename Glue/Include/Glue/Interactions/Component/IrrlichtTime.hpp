#pragma once

namespace Glue {
    class Time;
}

namespace Glue { namespace Irrlicht {
    Component;
}}

namespace Glue {

class IrrlichtTime
{
private:
    Irrlicht::Component* irrComp;
    Time* time;

public:
    IrrlichtTime(
        Irrlicht::Component* irrComp,
        Time* time
    );
    ~IrrlichtTime();
};

}
