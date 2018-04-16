#include <functional>
#include <stdexcept>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>

namespace StackStacking {

using Continuation = std::function<void()>;
using WorkFunc = std::function<void(Continuation)>;
using TaskList = std::vector<WorkFunc>;
using TaskIter = TaskList::const_iterator;
using TaskRange = std::pair<TaskIter, TaskIter>;

struct Trampoline
{
    TaskRange iters;

    void operator()() const
    {
        if (iters.first != iters.second)
            (*(iters.first++))(*this);
    }
};

void thingA(Continuation cc)
{
    std::cout << "Doing thing A\n";
    cc();
}

void thingB(Continuation cc)
{
    std::cout << "Doing thing B\n";
    cc();
}

void thingC(Continuation cc)
{
    std::cout << "From thing ...\n";
    throw std::logic_error("Whoa, how did we get here?");
}

void test_it()
{
    std::vector<TaskList> tasks = { thingA, thingB, thingC };
    Trampoline tramp = { tasks.begin(), tasks.end() };
    tramp();  // Start bouncing
}

}
