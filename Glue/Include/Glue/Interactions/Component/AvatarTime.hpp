#pragma once

namespace Glue {
    class Time;
}

namespace Glue { namespace Avatar {
    Component;
}}

namespace Glue {

class AvatarTime
{
private:
    Avatar::Component* avComp;
    Time* time;

public:
    AvatarTime(
        Avatar::Component* avComp,
        Time* time
    );
    ~AvatarTime();
};

}
