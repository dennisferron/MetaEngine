#pragma once

#include "Glue/Model/TimeComponent.hpp"
#include "Glue/Avatar/AvatarComponent.hpp"

namespace Glue {

class AvatarTime
{
private:
    Avatar::AvatarComponent* avComp;
    TimeComponent* time;

public:
    AvatarTime(
            Avatar::AvatarComponent* avComp,
            TimeComponent* time
    );
    ~AvatarTime();
};

}
