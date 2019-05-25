#include <boost/test/unit_test.hpp>
#include "Glue/Model/Graph.hpp"

using namespace Glue;

namespace {

template <typename Tag>
struct MockComponent
{
};

}

BOOST_AUTO_TEST_SUITE(ComponentsTests)

BOOST_AUTO_TEST_CASE(test_startup)
    {
        Graph graph;
    }

BOOST_AUTO_TEST_SUITE_END()