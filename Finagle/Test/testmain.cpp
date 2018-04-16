#include "Finagle/Finagle.hpp"
#include "NodeSyncTest.hpp"

namespace StackStacking {

void test_it();

}

namespace TestFinagle {

using Finagle;

int main(int, char**)
{
    StackStacking::test_it();
    return 0;
}

}
