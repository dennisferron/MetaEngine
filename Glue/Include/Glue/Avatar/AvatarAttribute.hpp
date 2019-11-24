#pragma once

#include <memory>

namespace Glue { namespace Avatar {

class AvatarAttribute
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    AvatarAttribute();
    ~AvatarAttribute();

    bool canJump();
    void dive();
    void jump();
    void right();
    void left();
};

}}
