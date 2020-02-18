#include "Glue/Bullet/BodyBuilder.hpp"
#include "Glue/Animators/KinematicAnimator.hpp"
#include "Glue/Animators/PhysicsAnimator.hpp"

#include "btRigidBody.h"

#include "Glue/Constants.hpp"

namespace
{
    using namespace Glue;
    using namespace Glue::Constants;

    btTransform get_shape_transform(NodeStyle const& style);
}

namespace Glue::Bullet
{
    btCollisionShape* BodyBuilder::createShape(
            NodeStyle const& style,
            irr::scene::IMesh* dispShapeMesh) const
    {
        auto physShape = create_physics_shape(style, dispShapeMesh);

        if (physShape != nullptr && style.margin)
            physShape->setMargin(*style.margin);

        return physShape;
    }

    btRigidBody::btRigidBodyConstructionInfo
        BodyBuilder::createConstructionInfo(
            NodeStyle const& style,
            btCollisionShape* physShape) const
    {
        if (physShape == nullptr)
            throw std::logic_error("physShape cannot be null");

        Scalar mass = style.isKinematic ? 0 : style.mass;

        auto localInertia = btVector3(0, 0, 0);

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

        auto shapeOffset = get_shape_transform(style);
        if (style.isKinematic)
            motionState = new KinematicAnimator(startTransform, shapeOffset);
        else
            motionState = new PhysicsAnimator(startTransform, shapeOffset);

        // This is done here rather than in ShapeBuilder because although bullet scales shapes,
        // irrlicht scales nodes, and the irrlicht node is only created in not in ShapeBuilder.
        // Also, some bullet shapes cannot be scaled anyway & have to be scaled here.
        physShape->setLocalScaling(btVector3(style.physScaleX, style.physScaleY, style.physScaleZ));

        auto rbInfo = btRigidBody::btRigidBodyConstructionInfo(
                mass,
                motionState,
                physShape,
                localInertia);
        rbInfo.m_friction = style.friction;

        return rbInfo;
    }

    std::unique_ptr<btRigidBody> BodyBuilder::addToWorld(
            NodeStyle const& style,
            btDynamicsWorld* dynamicsWorld,
            btRigidBody::btRigidBodyConstructionInfo const& rbInfo) const
    {
        auto rigidBody = std::make_unique<btRigidBody>(rbInfo);

        if (style.collisionGroup)
            dynamicsWorld->addRigidBody(rigidBody.get(), *style.collisionGroup, style.collisionMask);
        else
            dynamicsWorld->addRigidBody(rigidBody.get());

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

namespace
{
    using namespace Glue;
    using namespace Glue::Constants;

    btTransform get_shape_transform(NodeStyle const& style)
    {
        switch (style.physShape)
        {
            case ObjShapes::none:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::ball:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::box:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::cyl:
            {
                auto axis = btVector3(0, 1, 0);
                float angle = 0;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(0, -style.length / 2, 0);

                return btTransform(q, v);
            }
            case ObjShapes::cylX:
            {
                auto axis = btVector3(0, 0, 1);
                auto angle = TAU / 4;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(style.length / 2, 0, 0);

                return btTransform(q, v);
            }
            case ObjShapes::cylZ:
            {
                auto axis = btVector3(1, 0, 0);
                auto angle = TAU / 4;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(0, 0, -style.length / 2);

                return btTransform(q, v);
            }
            case ObjShapes::cone:
            {
                auto axis = btVector3(0, 0, 1);
                auto angle = 0;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(0, -style.length / 2, 0);

                return btTransform(q, v);
            }
            case ObjShapes::coneX:
            {
                auto axis = btVector3(0, 0, 1);
                auto angle = -TAU / 4;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(-style.length / 2, 0, 0);

                return btTransform(q, v);
            }
            case ObjShapes::coneZ:
            {
                auto axis = btVector3(1, 0, 0);
                auto angle = TAU / 4;
                auto q = btQuaternion(axis, angle);

                auto v = btVector3(0, 0, -style.length / 2);
                //auto v = btVector3(0, 0, 0);

                return btTransform(q, v);
            }
            case ObjShapes::hills:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::mesh:
            {
                return btTransform::getIdentity();
            }
            case ObjShapes::plane:
            {
                return btTransform::getIdentity();
            }
            default:
            {
                throw std::logic_error("Unknown ObjShape");
            }
        }
    }
}
