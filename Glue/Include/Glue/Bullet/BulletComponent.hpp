#pragma once

#include "Glue/Model/Component.hpp"

#include "Glue/Constants.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Bullet/BulletAttribute.hpp"

#include <functional>
#include <memory>


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

class BulletComponent : public Component
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    BulletComponent();
    ~BulletComponent();

    void setDebugMode(bool debugMode);
    void addLink(Link* link);
    void setDebugDrawer(btIDebugDraw* drawer);
    void setOnTick(std::function<void(TimeInfo)> aBlock);
    void setOnPreTick(std::function<void(TimeInfo)> aBlock);
    void onPhysics(Scalar timeElapsed);
    void onGraphics(Scalar timeElapsed);
    void removeConstraint(ConstraintObj* constraint);
    ConstraintObj* addConstraint(LinkStyle* style, btRigidBody& attrA, btRigidBody& attrB);
    BulletAttribute* addNode(Node* node);
};

}}
