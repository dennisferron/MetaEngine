#pragma once

#include <functional>

#include "Glue/Constants.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Bullet/NodeAttribute.hpp"

class btIDebugDraw;
class btRigidBody;

namespace Glue {
    class Link;
    class TimeInfo;
}

namespace Glue { namespace Bullet {
    class ConstraintObj;
}}

namespace Glue { namespace Bullet {

class Component
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    Component();
    ~Component();

    void setDebugMode(bool debugMode);
    void addLink(Link* link);
    void setDebugDrawer(btIDebugDraw* drawer);
    void setOnTick(std::function<void(TimeInfo)> aBlock);
    void setOnPreTick(std::function<void(TimeInfo)> aBlock);
    void onPhysics(Scalar timeElapsed);
    void onGraphics(Scalar timeElapsed);
    void removeConstraint(ConstraintObj* constraint);
    ConstraintObj* addConstraint(LinkStyle* style, btRigidBody& attrA, btRigidBody& attrB);
    NodeAttribute* addNode(Node* node);
};

}}
