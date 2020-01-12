#include "Glue/Bullet/BulletAttribute.hpp"

#include <vector>
#include <functional>

namespace Glue::Bullet
{
    BulletAttribute::BulletAttribute(
        NodeStyle const& style,
        btRigidBody* rigidBody,
        btMotionState* motionState
    ) :
        style(style),
        rigidBody(rigidBody),
        motionState(motionState)
    {
        rigidBody->setUserPointer(this);
    }

    BulletAttribute::~BulletAttribute()
    {
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
                obj := engine addObj(s)

                if(onTrigger != nil, onTrigger call(obj))
            )
            childObjs foreach(o, o triggerAllGenerators(onTrigger))
        )
 */
    }

    void BulletAttribute::lockTo(Node* otherObj)
    {}

    void BulletAttribute::applyForceTowards(btVector3 const& targetPos, Scalar scalar, Scalar maxForce)
    {}

    void BulletAttribute::applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                                           Scalar scalar, Scalar maxForce, Scalar maxVerticalForce)
    {}

    void BulletAttribute::applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                                           Scalar scalar, Scalar maxForce)
    {}

    void BulletAttribute::applyCentralForce(Scalar x, Scalar y, Scalar z)
    {}

    void BulletAttribute::applyCentralImpulse(Scalar x, Scalar y, Scalar z)
    {}

    void BulletAttribute::applyTorque(Scalar x, Scalar y, Scalar z)
    {
        rigidBody->applyTorque(btVector3(x, y, z));
    }

    void BulletAttribute::applyTorqueImpulse(Scalar x, Scalar y, Scalar z)
    {}

    void BulletAttribute::fallApart(std::vector<BulletAttribute*> visited,
                                    std::vector<BulletAttribute*> removed)
    {}

    void BulletAttribute::structureDoForEachObject(
            std::function<void(BulletAttribute*)> code,
            std::vector<BulletAttribute*> visited)
    {}

}

/*
        triggerAllGenerators := method(onTrigger,
            if (style hasSlot("spawnStyle"),
                s := style spawnStyle clone
                s setPos(s x + getX, s y + getY, s z + getZ)
                // TODO:  Set relative velocity as well as pos.
                obj := engine addObj(s)

                if(onTrigger != nil, onTrigger call(obj))
            )
            childObjs foreach(o, o triggerAllGenerators(onTrigger))
        )

        lockTo := method(otherObj,

            // In order to lock the object to another, we have to make it a kinematic body (i.e., directly animated not physically affected)
            CF_KINEMATIC_OBJECT := 2
            rigidBody setCollisionFlags(rigidBody getCollisionFlags | CF_KINEMATIC_OBJECT)
            DISABLE_DEACTIVATION := 4
            rigidBody setActivationState(DISABLE_DEACTIVATION)

            oldMotionState := motionState
            setMotionState(
                LockAnimator new(otherObj rigidBody getMotionState_c, namespace Bullet getIdentityTransform)
            )
            rigidBody setMotionState(motionState)

            if (node != nil,
                node addAnimator(motionState)
                node removeAnimator(oldMotionState)
            )

            oldMotionState drop

            motionState
        )

        applyForceTowards := method(targetPos, scalar, maxForce,
            p1 := targetPos
            p2 := getPos

            xdiff := p1 x - p2 x
            ydiff := p1 y - p2 y
            zdiff := p1 z - p2 z

            applyScaledForce(xdiff, ydiff, zdiff, scalar, maxForce)
        )

        applyScaledForce := method(xforce, yforce, zforce, scalar, maxForce, maxVerticalForce,

            if (maxVerticalForce == nil, maxVerticalForce = maxForce)

            xforce = xforce * scalar
            yforce = yforce * scalar
            zforce = zforce * scalar

            if (xforce > maxForce, xforce = maxForce)
            if (xforce < -maxForce, xforce = -maxForce)
            if (yforce > maxVerticalForce, yforce = maxVerticalForce)
            if (yforce < -maxVerticalForce, yforce = -maxVerticalForce)
            if (zforce > maxForce, zforce = maxForce)
            if (zforce < -maxForce, zforce = -maxForce)

            applyCentralForce(xforce, yforce, zforce)
        )

        applyCentralForce := method(x,y,z,
            rigidBody applyCentralForce(btVector3 tmp(x,y,z))
        )

        applyCentralImpulse := method(x,y,z,
            rigidBody applyCentralImpulse(btVector3 tmp(x,y,z))
        )

        applyTorque := method(x,y,z,
            rigidBody applyTorque(btVector3 tmp(x,y,z))
        )

        applyTorqueImpulse := method(x,y,z,
            rigidBody applyTorqueImpulse(btVector3 tmp(x,y,z))
        )

        fallApart := method(visited, removed,

            if (visited == nil,
                visited := list()
            )

            if (removed == nil,
                removed := list()
            )

            if (visited contains(self),
                return
            ,
                visited append(self)
            )

            consA := constraintsA clone
            consA foreach(c,
                if (c objB != nil,
                    c objB fallApart(visited, removed)
                )
                if (removed contains(c) not,
                    removed append(c)
                    engine removeConstraint(c)
                )
            )

            consB := constraintsB clone
            consB foreach(c,
                if (c objA != nil,
                    c objA fallApart(visited, removed)
                )
                if (removed contains(c) not,
                    removed append(c)
                    engine removeConstraint(c)
                )
            )

        )

        structureDoForEachObject := method(code, visited,

            if (visited == nil,
                visited := list()
            )

            if (visited contains(self),
                return
            ,
                visited append(self)
                code call(self)
            )

            consA := constraintsA clone
            consA foreach(c,
                if (c objB != nil,
                    c objB structureDoForEachObject(code, visited)
                )
            )

            consB := constraintsB clone
            consB foreach(c,
                if (c objA != nil,
                    c objA structureDoForEachObject(code, visited)
                )
            )
        )

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