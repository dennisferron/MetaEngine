#include "Glue/Bullet/BulletAttribute.hpp"

#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "btRigidBody.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <Glue/Animators/LockAnimator.hpp>

namespace
{
    bool contains(
        std::vector<Glue::Bullet::BulletAttribute*>& list,
        Glue::Bullet::BulletAttribute* ptr)
    {
        return std::find(
                list.begin(),
                list.end(),
                ptr) != list.end();
    }
}

namespace Glue::Bullet
{
    BulletAttribute::BulletAttribute(
        NodeStyle const& style,
        btRigidBody* rigidBody,
        MotionStateAnimator* motionState
    ) :
        style(style),
        rigidBody(rigidBody),
        motionState(motionState),
        sceneNode(nullptr)
    {
        rigidBody->setUserPointer(this);
    }

    BulletAttribute::~BulletAttribute()
    {
        dispose();
    }

    void BulletAttribute::dispose()
    {
        // If this is the left side of a constraint, delete not the constraint
        // but the object on the other side of the constraint.
        for (auto v : constraintsA)
        {
            // TODO:  Dispose, or delete?
            v->attrB->dispose();
        }
        constraintsA.clear();

        // If this is the right side of a constraint, remove the constraint
        // but not the A-side.
        for (auto v : constraintsB)
        {
            blt_cmp->removeConstraint(v->constraint);
            delete v->constraint;
        }
        constraintsB.clear();

        if (rigidBody)
        {
            blt_cmp->dynamicsWorld->removeRigidBody(rigidBody);
            delete rigidBody;
        }
    }

    btRigidBody& BulletAttribute::getRigidBody()
    {
        return *rigidBody;
    }

    btRigidBody& BulletAttribute::getRigidBody() const
    {
        return *rigidBody;
    }

    void addConstraintA(ConstraintObj* constraint)
    {}

    void addConstraintB(ConstraintObj* constraint)
    {}

    void removeConstraintA(ConstraintObj* constraint)
    {}

    void removeConstraintB(ConstraintObj* constraint)
    {}

    void BulletAttribute::setLinearVelocity(Scalar xv, Scalar yv, Scalar zv)
    {
        rigidBody->setLinearVelocity(btVector3(xv, yv, zv));
    }

    void BulletAttribute::setAngularVelocity(Scalar xv, Scalar yv, Scalar zv)
    {
        rigidBody->setAngularVelocity(btVector3(xv, yv, zv));
    }

    btVector3 const& BulletAttribute::getAngularVelocity() const
    {
        return rigidBody->getAngularVelocity();
    }

    btVector3 const& BulletAttribute::getLinearVelocity() const
    {
        return rigidBody->getLinearVelocity();
    }

    void BulletAttribute::addChild(Node* otherObj)
    {
        throw std::logic_error("No childObjs");
        //childObjs append(otherObj)
        //node addChild(otherObj node)
    }

    void BulletAttribute::disableSleepState()
    {
        // DISABLE_DEACTIVATION := 4
        rigidBody->setActivationState(DISABLE_DEACTIVATION);
    }

    Scalar BulletAttribute::getRotZ()
    {
        btQuaternion quat = rigidBody->getOrientation();

        btScalar w = quat.getW();
        btScalar x = quat.getX();
        btScalar y = quat.getY();
        btScalar z = quat.getZ();
        return atan2(
                2.0 * (x*y + z*w),
                (x*x - y*y - z*z + w*w));
    }

    btVector3 const& BulletAttribute::getPos()
    {
        if (rigidBody)
        {
            return rigidBody->getCenterOfMassPosition();
        }
        else
        {
            return { style.x, style.y, style.z };
        }
    }

    void BulletAttribute::triggerAllGenerators(std::function<void(Node*)> onTrigger)
    {
        throw std::logic_error("Not implemented");
/*
        triggerAllGenerators := method(onTrigger,
            if (style hasSlot("spawnStyle"),
                s := style spawnStyle clone
                s setPos(s x + getX, s y + getY, s z + getZ)
                // TODO:  Set relative velocity as well as pos.
                obj := engine addObj(s)  // engine is actually blt_cmp

                if(onTrigger != nil, onTrigger call(obj))
            )
            childObjs foreach(o, o triggerAllGenerators(onTrigger))
        )
 */
    }

    void BulletAttribute::lockTo(BulletAttribute* otherObj)
    {
        // In order to lock the object to another, we have to make it a kinematic body
        // (i.e., directly animated not physically affected)
        constexpr int CF_KINEMATIC_OBJECT = 2;
        rigidBody->setCollisionFlags(
            rigidBody->getCollisionFlags() |
            CF_KINEMATIC_OBJECT);

        //DISABLE_DEACTIVATION := 4
        rigidBody->setActivationState(DISABLE_DEACTIVATION);

        MotionStateAnimator* oldMotionState = this->motionState;
        this->motionState = new LockAnimator(
                otherObj->rigidBody->getMotionState(),
                btTransform::getIdentity());

        rigidBody->setMotionState(this->motionState);

        if (this->sceneNode)
        {
            sceneNode->addAnimator(motionState);
            sceneNode->removeAnimator(oldMotionState);
        }

        oldMotionState->drop();
    }

    void BulletAttribute::applyForceTowards(btVector3 const& targetPos, Scalar scalar, Scalar maxForce)
    {
        btVector3 p1 = targetPos;
        btVector3 p2 = getPos();

        Scalar xdiff = p1.x() - p2.x();
        Scalar ydiff = p1.y() - p2.y();
        Scalar zdiff = p1.z() - p2.z();

        applyScaledForce(xdiff, ydiff, zdiff, scalar, maxForce);
    }

    void BulletAttribute::applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                                           Scalar scalar, Scalar maxForce, Scalar maxVerticalForce)
    {
        xforce = xforce * scalar;
        yforce = yforce * scalar;
        zforce = zforce * scalar;

        if (xforce > maxForce) xforce = maxForce;
        if (xforce < -maxForce) xforce = -maxForce;
        if (yforce > maxVerticalForce) yforce = maxVerticalForce;
        if (yforce < -maxVerticalForce) yforce = -maxVerticalForce;
        if (zforce > maxForce) zforce = maxForce;
        if (zforce < -maxForce) zforce = -maxForce;

        applyCentralForce(xforce, yforce, zforce);
    }

    void BulletAttribute::applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                                           Scalar scalar, Scalar maxForce)
    {
        applyScaledForce(xforce, yforce, zforce, scalar, maxForce, maxForce);
    }

    void BulletAttribute::applyCentralForce(Scalar x, Scalar y, Scalar z)
    {
        rigidBody->applyCentralForce(btVector3(x,y,z));
    }

    void BulletAttribute::applyCentralImpulse(Scalar x, Scalar y, Scalar z)
    {
        rigidBody->applyCentralImpulse(btVector3(x,y,z));
    }

    void BulletAttribute::applyTorque(Scalar x, Scalar y, Scalar z)
    {
        rigidBody->applyTorque(btVector3(x, y, z));
    }

    void BulletAttribute::applyTorqueImpulse(Scalar x, Scalar y, Scalar z)
    {
        rigidBody->applyTorqueImpulse(btVector3(x,y,z));
    }

    void BulletAttribute::fallApart()
    {
        std::vector<BulletAttribute*> visited;
        std::vector<BulletAttribute*> removed;
        fallApart(visited, removed);
    }

    void BulletAttribute::fallApart(std::vector<BulletAttribute*>& visited,
                                    std::vector<BulletAttribute*>& removed)
    {
        if (contains(visited, this))
            return;
        else
            visited.push_back(this);

        std::vector<ConstraintObj*> consA(constraintsA);
        for (auto c : consA)
        {
            if (c->attrB)
                c->attrB->fallApart(visited, removed);
            if (!contains(removed, c))
            {
                removed.push_back(c);
                blt_cmp->removeConstraint(c);
            }
        }

        std::vector<ConstraintObj*> consB(constraintsB);
        for (auto c : consB)
        {
            if (c->attrA)
                c->attrA->fallApart(visited, removed);
            if (!contains(removed, c))
            {
                removed.push_back(c);
                blt_cmp->removeConstraint(c);
            }
        }
    }

    void BulletAttribute::structureDoForEachObject(
            std::function<void(BulletAttribute*)> code)
    {
        std::vector<BulletAttribute*> visited;
        structureDoForEachObject(code, visited);
    }

    void BulletAttribute::structureDoForEachObject(
            std::function<void(BulletAttribute*)> code,
            std::vector<BulletAttribute*>& visited)
    {
        if (contains(visited, this))
            return;
        else
        {
            visited.push_back(this);
            code(this);
        }

        std::vector<ConstraintObj*> consA(constraintsA);
        for (auto c : consA)
        {
            if (c->attrB)
                c->attrB->structureDoForEachObject(code, visited);
        }

        std::vector<ConstraintObj*> consB(constraintsB);
        for (auto c : consB)
        {
            if (c->attrA)
                c->attrA->structureDoForEachObject(code, visited);
        }
    }

}

/*

        dispose := method(

            // If this is the left side of a constraint, delete not the constraint
            // but the object on the other side of the constraint.
            constraintsA foreach(v, v objB dispose)
            constraintsA empty

            // If this is the right side of a constraint, remove the constraint but not the A-side.
            constraintsB foreach(v, engine removeConstraint(v constraint); constraint delete)
            constraintsB empty

            if (rigidBody != nil,
                engine dynamicsWorld removeRigidBody(rigidBody)
                rigidBody delete
            )
        )
    )
)
*/