#pragma once

#include <memory>

namespace Glue {
    class Node;
    class TimeInfo;
}

namespace Glue { namespace Avatar {

class Component
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    Component();
    ~Component();

    void attachControl(Node* node);
    void beforePhysics(TimeInfo const&);
};

}}
