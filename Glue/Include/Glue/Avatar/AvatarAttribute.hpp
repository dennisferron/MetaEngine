#pragma once

#include "Glue/Avatar/AvatarInterfaces.hpp"

namespace Glue::Avatar
{

class AvatarAttribute : public IAvatarAttribute
{
public:
    AvatarAttribute();
    ~AvatarAttribute();

    bool canJump();
    void dive();
    void jump();
    void right();
    void left();
};

}
