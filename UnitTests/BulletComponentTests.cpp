#include "boost/test/unit_test.hpp"

#include "BulletMocks.hpp"
#include "ModelMocks.hpp"

#include "Glue/Bullet/BulletComponent.hpp"

#include <string>

using namespace Glue;
using namespace Glue::Bullet;

BOOST_AUTO_TEST_SUITE(BulletComponentsTests)

    BOOST_AUTO_TEST_CASE(test_add_shape)
    {
        btScalar mass = 0;
        btMotionState* motionState = nullptr;
        btCollisionShape* shape = nullptr;
        btVector3 localInertia=btVector3(0,0,0):

        btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, localInertia);
        btRigidBody* body = nullptr;

        MockBodyBuilder mock_body_builder;
        MockConstraintBuilder mock_constraint_builder;

        BulletComponent bullet_component(&mock_body_builder, &mock_constraint_builder);

        MockShape mock_shape;
        auto attribute = bullet_component.addShape(&mock_shape);

    }

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
    MockShape mock_shape(shape_style);

    NodeStyle node_style;
    MockNode mock_node(node_style, &mock_shape);

    IBulletAttribute* result = std::get<IBulletAttribute*>(blt_cmp.addNode(&mock_node));
    btVector3 pos = result->getPos();
}

BOOST_AUTO_TEST_SUITE_END()