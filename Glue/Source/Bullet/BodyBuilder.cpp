#include "Glue/Bullet/BodyBuilder.hpp"
#include "Glue/Animators/KinematicAnimator.hpp"
#include "Glue/Animators/PhysicsAnimator.hpp"

namespace Glue::Bullet
{
    BodyBuilder::BodyBuilder(btDynamicsWorld* dynamicsWorld, ShapeBuilder* shapeBuilder)
        : dynamicsWorld(dynamicsWorld), shapeBuilder(shapeBuilder)
    {
    }

    btRigidBody* BodyBuilder::buildBody(NodeStyle const& style) const
    {
        auto physShape = shapeBuilder->create(style);
        auto shapeOffset = shapeBuilder->getOffset(style);

        if (physShape == nullptr)
            return nullptr;

        Scalar mass = style.isKinematic ? 0 : style.mass;

        auto localInertia = btVector3(0,0,0);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        if (mass != 0)
            physShape->calculateLocalInertia(style.mass, localInertia);

        // Location
        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(style.x, style.y, style.z));

        btQuaternion rot;

        if (style.axisX == 0 && style.axisY == 0 && style.axisZ == 0)
            rot = btQuaternion(style.yaw, style.pitch, style.roll);
        else
            rot = btQuaternion(
                    btVector3(style.axisX, style.axisY, style.axisZ),
                    style.angle);

        startTransform.setRotation(rot);

        btMotionState* motionState;

        if (style.isKinematic)
            motionState = new KinematicAnimator(startTransform, shapeOffset);
        else
            motionState = new PhysicsAnimator(startTransform, shapeOffset);

        // This is done here rather than in ShapeBuilder because although bullet scales shapes,
        // irrlicht scales nodes, and the irrlicht node is only created in not in ShapeBuilder.
        // Also, some bullet shapes cannot be scaled anyway & have to be scaled here.
        physShape->setLocalScaling(btVector3(style.physScaleX, style.physScaleY, style.physScaleZ));

        auto rbInfo = btRigidBody::btRigidBodyConstructionInfo(mass, motionState, physShape, localInertia);
        rbInfo.m_friction = style.friction;

        auto rigidBody = new btRigidBody(rbInfo);

        if (style.collisionGroup)
            dynamicsWorld->addRigidBody(rigidBody, *style.collisionGroup, style.collisionMask);
        else
            dynamicsWorld->addRigidBody(rigidBody);

        rigidBody->setLinearFactor(btVector3(style.linFactorX, style.linFactorY, style.linFactorZ));
        rigidBody->setAngularFactor(btVector3(style.angFactorX, style.angFactorY, style.angFactorZ));

        rigidBody->setDamping(style.linDamping, style.angDamping);

        // Must set gravity after adding to dynamics world, or it gets overwritten with the default gravity.
        if (style.gravityType == GravityType::none)
            rigidBody->setGravity(btVector3(0,0,0));
        else if (style.gravityType == GravityType::custom)
            rigidBody->setGravity(btVector3(*style.gravityX, *style.gravityY, *style.gravityZ));

        rigidBody->setLinearVelocity(btVector3(style.xv, style.yv, style.zv));

        // Static mesh objects can be kinematic as well as rigid bodies.
        // I think this is safe for softbody too, although a kinematic softbody
        // doesn't really make a lot of sense.
        if (style.isKinematic)
        {
            rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
            rigidBody->setActivationState(DISABLE_DEACTIVATION);
        }

        if (style.disableDeactivation)
        {
            rigidBody->setActivationState(DISABLE_DEACTIVATION);
        }

        // Restitution applies to static mesh objects and to rigid bodies.
        if (style.restitution)
        {
            rigidBody->setRestitution(*style.restitution);
        }

        return rigidBody;
    }
}
