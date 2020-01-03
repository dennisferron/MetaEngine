#include "boost/test/unit_test.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Bullet/BulletComponentImpl.hpp"

#include <string>

namespace
{
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

    };
}

BOOST_AUTO_TEST_SUITE(BulletComponentsTests)

BOOST_AUTO_TEST_CASE(test_something)
{
    auto shapeBuilder = new MockBodyBuilder();
    Glue::Bullet::BulletComponentImpl blt_cmp(shapeBuilder);
}

BOOST_AUTO_TEST_SUITE_END()