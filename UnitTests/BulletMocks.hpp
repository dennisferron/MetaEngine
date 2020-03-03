#pragma once

#include "Glue/Bullet/BulletInterfaces.hpp"

namespace
{
    using namespace Glue;
    using namespace Glue::Bullet;

    class MockDebugDrawer : public btIDebugDraw
    {
    public:
        bool drew_line = false;

        virtual void drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
        {
            drew_line = true;
        }
    };

    class MockBodyBuilder : public Glue::Bullet::IBodyBuilder
    {
    public:
        btCollisionShape* shape;
        btRigidBody::btRigidBodyConstructionInfo info;
        btRigidBody* body;

        MockBodyBuilder(
                btCollisionShape* shape,
                btRigidBody::btRigidBodyConstructionInfo info,
                btRigidBody* body) :
                shape(shape),
                info(info),
                body(body)
        {
        }

        btCollisionShape* createShape(
                NodeStyle const& style,
                irr::scene::IMesh* dispShapeMesh
        ) const override
        {
            return shape;
        }

        Glue::Bullet::BodyConstructionInfo
        createConstructionInfo(
                NodeStyle const& style,
                btCollisionShape* physShape
        ) const override
        {
            MotionStateAnimator* ms = nullptr;
            return  { info, ms };
        }

        btRigidBody* addToWorld(
                NodeStyle const& style,
                btDynamicsWorld* dynamicsWorld,
                btRigidBody::btRigidBodyConstructionInfo const& rbInfo
        ) const override
        {
            return body;
        }
    };

    class MockConstraintBuilder : public Glue::Bullet::IConstraintBuilder
    {
    public:
        IConstraintObj* create(ConstraintStyle const& style, btRigidBody* objA, btRigidBody* objB)  override
        {
            return nullptr;
        }
    };
}