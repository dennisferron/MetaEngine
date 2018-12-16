#pragma once

#include "Glue/Model/Time.hpp"
#include "Glue/Avatar/Component.hpp"

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
