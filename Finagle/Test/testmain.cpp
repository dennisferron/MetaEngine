#include "Finagle/Finagle.hpp"
#include "NodeSyncTest.hpp"

namespace TestFinagle {

using Finagle;

int main(int, char**)
{
    Graph graph;

    graph.add_component(new PhysComp());
    graph.add_component(new ViewComp());

    return 0;
}

}
