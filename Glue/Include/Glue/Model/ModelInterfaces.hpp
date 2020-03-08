#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Styles/ConstraintStyle.hpp"

#include "ISceneNode.h"

#include "Glue/Model/ITimeComponent.hpp"

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <set>

namespace Glue
{
    class Shape;
    class Node;
    class Link;
    class Structure;
    class Graph;

    template <typename T, typename U>
    T* find_attribute(U const* u)
    {
        T* t;
        for (auto p : u->get_attributes())
        {
            if (t = dynamic_cast<T*>(p))
                return t;
        }
        return nullptr;
    }

    class NodeAttribute
    {
    public:
        virtual ~NodeAttribute(){}
    };

    class LinkAttribute
    {
    public:
        virtual ~LinkAttribute() {}
    };

    class ShapeAttribute
    {
    public:
        virtual ~ShapeAttribute() {}
    };

    class IGraphObserver
    {
    public:
        virtual ShapeAttribute* addShape(Shape* shape) = 0;
        virtual NodeAttribute* addNode(Node* node) = 0;
        virtual LinkAttribute* addLink(Link* link) = 0;
    };
}
