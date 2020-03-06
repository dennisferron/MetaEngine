#include "Glue/Model/Node.hpp"

#include "Glue/Utility/variant_helpers.hpp"

namespace Glue
{

Node::Node(NodeStyle const& style, IShape* shape) :
    style(style), shape(shape)
{
}

Node::~Node()
{
}

NodeStyle const& Node::get_style() const
{
    return style;
}

IShape* Node::get_shape() const
{
    return shape;
}

std::vector<NodeAttribute*> const& Node::get_attributes() const
{
    return attributes;
}

    void Node::addAttribute(NodeAttribute* attr)
    {
        // TODO:  Handle interactions; only push_back after that.
        attributes.push_back(attr);
    }

} // namespace Glue
