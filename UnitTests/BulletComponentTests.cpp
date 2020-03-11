#include "boost/test/unit_test.hpp"

#include "BulletMocks.hpp"
#include "ModelMocks.hpp"

#include "Glue/Bullet/BulletComponent.hpp"

#include "Glue/Model/Shape.hpp"
#include "Glue/Model/Node.hpp"

#include <string>

using namespace Glue;
using namespace Glue::Bullet;

BOOST_AUTO_TEST_SUITE(BulletComponentsTests)

    BOOST_AUTO_TEST_CASE(test_add_shape)
    {
        btScalar mass = 0;
        btMotionState* motionState = nullptr;
        btCollisionShape* col_shape = nullptr;
        btVector3 localInertia=btVector3(0,0,0);

        btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, col_shape, localInertia);
        btRigidBody* body = nullptr;

        MockBodyBuilder mock_body_builder(col_shape, info, body);
        MockConstraintBuilder mock_constraint_builder;

        BulletComponent bullet_component(&mock_body_builder, &mock_constraint_builder);

        ShapeStyle shape_style;
        Shape shape(shape_style);
        auto attribute = bullet_component.addShape(&shape);
        BOOST_CHECK(attribute);
    }

BOOST_AUTO_TEST_CASE(test_something)
{
    btCollisionShape* col_shape = new btSphereShape(1);

    btScalar mass = 1;
    btVector3 inertia(0, 0, 0);
    col_shape->calculateLocalInertia(mass, inertia);

    btDefaultMotionState* motionState =
            new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));

    btRigidBody::btRigidBodyConstructionInfo info(
            mass, motionState, col_shape, inertia);

    btRigidBody* body = new btRigidBody(info);

    auto bodyBuilder = new MockBodyBuilder(col_shape, info, body);
    auto constrBuilder = new MockConstraintBuilder();
    Glue::Bullet::BulletComponent blt_cmp(bodyBuilder, constrBuilder);

    ShapeStyle shape_style;
    Shape shape(shape_style);

    NodeStyle node_style;
    Node node(node_style, &shape);

    IBulletAttribute* result = dynamic_cast<IBulletAttribute*>(blt_cmp.addNode(&node));
    btVector3 pos = result->getPos();
}

BOOST_AUTO_TEST_SUITE_END()