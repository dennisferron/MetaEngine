#include "boost/test/unit_test.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Bullet/BulletComponentImpl.hpp"

#include <string>

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

    class MockBodyBuilder : public Glue::Bullet::BodyBuilder
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

        btRigidBody::btRigidBodyConstructionInfo
            createConstructionInfo(
                NodeStyle const& style,
                btCollisionShape* physShape
        ) const override
        {
            return info;
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
}

BOOST_AUTO_TEST_SUITE(BulletComponentsTests)

BOOST_AUTO_TEST_CASE(test_something)
{
    btCollisionShape* shape = new btSphereShape(1);

    btScalar mass = 1;
    btVector3 inertia(0, 0, 0);
    shape->calculateLocalInertia(mass, inertia);

    btDefaultMotionState* motionState =
            new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));

    btRigidBody::btRigidBodyConstructionInfo info(
            mass, motionState, shape, inertia);

    btRigidBody* body = new btRigidBody(info);

    auto bodyBuilder = new MockBodyBuilder(shape, info, body);
    Glue::Bullet::BulletComponentImpl blt_cmp(bodyBuilder);

    NodeStyle style;
    Node mock_node(style);

    BulletAttribute* result = blt_cmp.addNode(&mock_node);
    btVector3 pos = result->getPos();
}

BOOST_AUTO_TEST_SUITE_END()