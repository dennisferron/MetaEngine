#include "boost/test/unit_test.hpp"

#include "Glue/Model/Graph.hpp"
#include "Glue/Model/Shape.hpp"
#include "Glue/Model/Node.hpp"

using namespace Glue;

BOOST_AUTO_TEST_SUITE(GraphTests)

    BOOST_AUTO_TEST_CASE(test_graph_add_shape)
    {
        Graph graph;

        ShapeStyle style;
        Shape* shape; // = new Shape(style);
        graph.addShape(shape);

        // TODO:  Check a graph observer got notified
        //BOOST_CHECK_EQUAL(name, "test");
    }

    BOOST_AUTO_TEST_CASE(test_graph_add_node)
    {
        Graph graph;

        NodeStyle style;
        //Node node(style, nullptr);
        //graph.addNode(&node);

        // TODO:  Check a graph observer got notified
        //BOOST_CHECK_EQUAL(name, "test");
    }

BOOST_AUTO_TEST_SUITE_END()

