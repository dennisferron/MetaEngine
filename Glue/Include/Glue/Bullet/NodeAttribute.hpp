#pragma once

#include <functional>
#include <memory>

class btVector3;

namespace Glue {
    using Scalar = double;
    class Node;
}

namespace Glue { namespace Bullet {

class NodeAttribute
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    NodeAttribute(Node* node);
    ~NodeAttribute();

    void setLinearVelocity(Scalar xv, Scalar yv, Scalar zv);
    void setAngularVelocity(Scalar xv, Scalar yv, Scalar zv);
    void applyTorque(Scalar x, Scalar y, Scalar z);
    btVector3 const& getAngularVelocity() const;
    btVector3 const& getLinearVelocity() const;
    void addChild(Node* otherObj);
    void disableSleepState();
    Scalar getRotZ();
    btVector3 const& getPos();
    void triggerAllGenerators(std::function<void(Node*)> onTrigger);
    void lockTo(Node* otherObj);
    void applyForceTowards(btVector3 const& targetPos, Scalar scalar, Scalar maxForce);
    void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                          Scalar scalar, Scalar maxForce, Scalar maxVerticalForce);
    void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                          Scalar scalar, Scalar maxForce);
    void applyCentralForce(Scalar x, Scalar y, Scalar z);
    void applyCentralImpulse(Scalar x, Scalar y, Scalar z);
    void applyTorque(Scalar x, Scalar y, Scalar z);
    void applyTorqueImpulse(Scalar x, Scalar y, Scalar z);
    void fallApart(std::vector<NodeAttribute*> visited,
                   std::vector<NodeAttribute*> removed);
    void structureDoForEachObject(
                    std::function<NodeAttribute*> code,
                    std::vector<NodeAttribute*> visited);
};

}}
