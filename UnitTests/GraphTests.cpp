#include "boost/test/unit_test.hpp"
#include "Glue/Model/Graph.hpp"

using namespace Glue;

BOOST_AUTO_TEST_SUITE(GraphTests)

    BOOST_AUTO_TEST_CASE(test_graph_add_shape)
    {
        Graph graph;

        NodeStyle style;
        graph.addNode(style, nullptr);

        //BOOST_CHECK_EQUAL(name, "test");
    }

    BOOST_AUTO_TEST_CASE(test_graph_add_node)
    {
        Graph graph;

        NodeStyle style;
        graph.addNode(style, nullptr);

        //BOOST_CHECK_EQUAL(name, "test");
    }

BOOST_AUTO_TEST_SUITE_END()

