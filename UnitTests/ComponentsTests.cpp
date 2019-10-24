#include "boost/test/unit_test.hpp"
#include "Glue/Model/Graph.hpp"
#include "MockComponents.hpp"

#include <string>

using namespace Glue;

namespace {

    struct MockComponent1 : Glue::Component
    {
        std::string name = "Component One";
    };

    struct MockComponent2 : Glue::Component
    {
        std::string name = "Component Two";
    };

}

BOOST_AUTO_TEST_SUITE(ComponentsTests)

BOOST_AUTO_TEST_CASE(test_graph)
    {
        Graph graph;

        MockComponent1 mc1;
        graph.addComponent(&mc1);

        MockComponent2 mc2;
        graph.addComponent(&mc2);
    }

BOOST_AUTO_TEST_SUITE_END()