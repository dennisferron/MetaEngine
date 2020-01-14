#pragma once

#include <functional>
#include <memory>
#include <Glue/Styles/Styles.hpp>

#include "Glue/Constants.hpp"
#include "ConstraintObj.hpp"

#include "Glue/Model/Node.hpp"

#include "btRigidBody.h"
#include "Glue/Animators/MotionStateAnimator.hpp"

#include "ISceneNode.h"

namespace Glue::Bullet
{

    class BulletAttribute
    {
    private:
        NodeStyle style;
        btRigidBody* rigidBody;
        MotionStateAnimator* motionState;
        irr::scene::ISceneNode* sceneNode;
        std::vector<ConstraintObj*> constraintsA;
        std::vector<ConstraintObj*> constraintsB;

        void dispose();

    public:

        BulletAttribute(
                NodeStyle const& style,
                btRigidBody* rigidBody,
                MotionStateAnimator* motionState
        );

        ~BulletAttribute();

        btRigidBody& getRigidBody();

        btRigidBody& getRigidBody() const;

        void addConstraintA(ConstraintObj* constraint);

        void addConstraintB(ConstraintObj* constraint);

        void removeConstraintA(ConstraintObj* constraint);

        void removeConstraintB(ConstraintObj* constraint);

        void setLinearVelocity(Scalar xv, Scalar yv, Scalar zv);

        void setAngularVelocity(Scalar xv, Scalar yv, Scalar zv);

        btVector3 const& getAngularVelocity() const;

        btVector3 const& getLinearVelocity() const;

        void addChild(Node* otherObj);

        void disableSleepState();

        Scalar getRotZ();

        btVector3 const& getPos();

        void triggerAllGenerators(std::function<void(Node*)> onTrigger);

        void lockTo(BulletAttribute* otherObj);

        void applyForceTowards(btVector3 const& targetPos, Scalar scalar, Scalar maxForce);

        void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                              Scalar scalar, Scalar maxForce, Scalar maxVerticalForce);

        void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                              Scalar scalar, Scalar maxForce);

        void applyCentralForce(Scalar x, Scalar y, Scalar z);

        void applyCentralImpulse(Scalar x, Scalar y, Scalar z);

        void applyTorque(Scalar x, Scalar y, Scalar z);

        void applyTorqueImpulse(Scalar x, Scalar y, Scalar z);

        void fallApart();

        void fallApart(std::vector<BulletAttribute*>& visited,
                       std::vector<BulletAttribute*>& removed);

        void structureDoForEachObject(
                std::function<void(BulletAttribute*)> code);

        void structureDoForEachObject(
                std::function<void(BulletAttribute*)> code,
                std::vector<BulletAttribute*>& visited);
    };

}
