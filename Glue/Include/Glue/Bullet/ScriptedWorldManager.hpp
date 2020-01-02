#pragma once

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "Glue/Model/TimeComponent.hpp"

#include <functional>
#include <optional>

namespace Glue::Bullet {

using TickHandler = std::function<void(btDynamicsWorld*,btScalar)>;

class ScriptedWorldManager
{
public:

    void setOnTick(btDynamicsWorld& world, TickHandler onTick_);
    void setOnPreTick(btDynamicsWorld& world, TickHandler onPreTick_);

private:
    std::optional<TickHandler> onPreTick;
    std::optional<TickHandler> onTick;

    static void static_tick_callback(btDynamicsWorld *world, btScalar timeStep);
    void tick_callback(btDynamicsWorld *world, btScalar timeStep);

    static void static_pretick_callback(btDynamicsWorld *world, btScalar timeStep);
    void pretick_callback(btDynamicsWorld *world, btScalar timeStep);
};

}
