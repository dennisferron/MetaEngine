#pragma once

#include <functional>
#include <memory>
#include "Glue/Styles/Styles.hpp"

#include "Glue/Bullet/BulletInterfaces.hpp"
#include "Glue/Constants.hpp"

#include "Glue/Model/Node.hpp"

#include "btRigidBody.h"
#include "Glue/Animators/MotionStateAnimator.hpp"

#include "ISceneNode.h"

#include <memory>

namespace Glue::Bullet
{
    class BulletAttribute : public IBulletAttribute
    {
    private:
        NodeStyle style;
        std::unique_ptr<btRigidBody> rigidBody;
        MotionStateAnimator* motionState;
        IBulletComponent* blt_cmp;
        irr::scene::ISceneNode* sceneNode;
        std::vector<IConstraintObj*> constraintsA;
        std::vector<IConstraintObj*> constraintsB;

        void dispose();

    public:

        BulletAttribute(
                NodeStyle const& style,
                std::unique_ptr<btRigidBody>&& rigidBody,
                MotionStateAnimator* motionState,
                IBulletComponent* blt_cmp
        );

        ~BulletAttribute();

        btRigidBody* getRigidBody() const final;

        void addConstraintA(IConstraintObj* constraint) final;

        void addConstraintB(IConstraintObj* constraint) final;

        void removeConstraintA(IConstraintObj* constraint) final;

        void removeConstraintB(IConstraintObj* constraint) final;

        void setLinearVelocity(Scalar xv, Scalar yv, Scalar zv) final;

        void setAngularVelocity(Scalar xv, Scalar yv, Scalar zv) final;

        btVector3 getAngularVelocity() const final;

        btVector3 getLinearVelocity() const final;

        void addChild(INode* otherObj) final;

        void disableSleepState() final;

        Scalar getRotZ() const final;

        btVector3 getPos() const final;

        void triggerAllGenerators(std::function<void(INode*)> onTrigger) final;

        void lockTo(IBulletAttribute* otherObj) final;

        void applyForceTowards(btVector3 const& targetPos, Scalar scalar, Scalar maxForce) final;

        void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                              Scalar scalar, Scalar maxForce, Scalar maxVerticalForce) final;

        void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                              Scalar scalar, Scalar maxForce) final;

        void applyCentralForce(Scalar x, Scalar y, Scalar z) final;

        void applyCentralImpulse(Scalar x, Scalar y, Scalar z) final;

        void applyTorque(Scalar x, Scalar y, Scalar z) final;

        void applyTorqueImpulse(Scalar x, Scalar y, Scalar z) final;

        void fallApart() final;

        void structureDoForEachObject(
                std::function<void(IBulletAttribute*)> code) final;

        void fallApart(std::vector<IBulletAttribute*>& visited,
                       std::vector<IConstraintObj*>& removed) final;

        void structureDoForEachObject(
                std::function<void(IBulletAttribute*)> code,
                std::vector<IBulletAttribute*>& visited) final;
    };

}
