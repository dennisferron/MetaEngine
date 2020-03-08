#pragma once

#include "Glue/Model/ModelInterfaces.hpp"

namespace
{
    using namespace Glue;

    class MockGraphObserver : public IGraphObserver
    {
    public:
        ShapeAttribute* addShape(Shape* shape) override{ return nullptr; }
        NodeAttribute* addNode(Node* node) override{return nullptr;}
        LinkAttribute* addLink(Link* link) override{return nullptr;}
    };
}