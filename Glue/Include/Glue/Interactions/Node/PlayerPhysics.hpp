#pragma once

#include "btVector3.h"

#include <memory>

namespace Glue {

class PlayerPhysics
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    PlayerPhysics();
    ~PlayerPhysics();

    btVector3 const& vel() const;
    void debugVel() const;

    void right();
    void left();
    void dive();
    void jump();
};

}
