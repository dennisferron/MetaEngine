#include "boost/test/unit_test.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Bullet/BulletComponent.hpp"
#include "Glue/Model/Node.hpp"

#include <string>
#include <Glue/Model/Shape.hpp>
#include <Glue/Bullet/BulletAttribute.hpp>

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
    auto constrBuilder = new MockConstraintBuilder();
    Glue::Bullet::BulletComponent blt_cmp(bodyBuilder, constrBuilder);

    ShapeStyle shape_style;
    Glue::Shape node_shape(shape_style);

    NodeStyle node_style;
    Node mock_node(node_style, &node_shape);

    IBulletAttribute* result = std::get<IBulletAttribute*>(blt_cmp.addNode(&mock_node));
    btVector3 pos = result->getPos();
}

BOOST_AUTO_TEST_SUITE_END()