#pragma once

#include "Glue/Model/Time.hpp"
#include "Glue/Avatar/AvatarComponent.hpp"

namespace Glue {

class AvatarTime
{
private:
    Avatar::AvatarComponent* avComp;
    Time* time;

public:
    AvatarTime(
        Avatar::AvatarComponent* avComp,
        Time* time
    );
    ~AvatarTime();
};

}
