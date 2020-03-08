#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Model/ModelInterfaces.hpp"

#include <vector>

#include <memory>

namespace Glue
{
    // Visitor for NodeAttribute
    class NodeInteractions
    {
        // TODO:  Add member variables for interactions.
    };

class Node
{
private:
    NodeStyle style;
    Shape* shape;
    NodeInteractions interactions;
    std::vector<NodeAttribute*> attributes;

public:

    Node(NodeStyle const& style, Shape* shape);
    ~Node();

    Shape* get_shape() const;
    NodeStyle const& get_style() const;
    void addAttribute(NodeAttribute* attr);
    std::vector<NodeAttribute*> const& get_attributes() const;
};

}
