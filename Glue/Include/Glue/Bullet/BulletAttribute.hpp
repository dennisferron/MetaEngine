#pragma once

#include <functional>
#include <memory>

#include "Glue/Constants.hpp"

class btVector3;

namespace Glue {
    class Node;
}

namespace Glue::Bullet {

    class BulletAttribute
    {
    private:
        class Impl;

        std::unique_ptr<Impl> impl;

    public:

        BulletAttribute(Node *node);

        ~BulletAttribute();

        void setLinearVelocity(Scalar xv, Scalar yv, Scalar zv);

        void setAngularVelocity(Scalar xv, Scalar yv, Scalar zv);

        btVector3 const &getAngularVelocity() const;

        btVector3 const &getLinearVelocity() const;

        void addChild(Node *otherObj);

        void disableSleepState();

        Scalar getRotZ();

        btVector3 const &getPos();

        void triggerAllGenerators(std::function<void(Node *)> onTrigger);

        void lockTo(Node *otherObj);

        void applyForceTowards(btVector3 const &targetPos, Scalar scalar, Scalar maxForce);

        void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                              Scalar scalar, Scalar maxForce, Scalar maxVerticalForce);

        void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                              Scalar scalar, Scalar maxForce);

        void applyCentralForce(Scalar x, Scalar y, Scalar z);

        void applyCentralImpulse(Scalar x, Scalar y, Scalar z);

        void applyTorque(Scalar x, Scalar y, Scalar z);

        void applyTorqueImpulse(Scalar x, Scalar y, Scalar z);

        void fallApart(std::vector<BulletAttribute *> visited,
                       std::vector<BulletAttribute *> removed);

        void structureDoForEachObject(
                std::function<void(BulletAttribute *)> code,
                std::vector<BulletAttribute *> visited);
    };

}
