#include "Glue/Model/Link.hpp"
#include "Glue/Model/Node.hpp"
#include "Glue/Model/Graph.hpp"

namespace Glue {

Link::Link(LinkStyle const& style, Node* fromNode, Node* toNode) :
    style(style),
    fromNode(fromNode),
    toNode(toNode)
{
}

LinkStyle const& Link::get_style() const
{
    return style;
}

Node* Link::get_fromNode() const
{
    return fromNode;
}

Node* Link::get_toNode() const
{
    return toNode;
}

void Link::addAttribute(LinkAttribute* attr)
{
    attributes.push_back(attr);
}

std::vector<LinkAttribute*> const& Link::get_attributes() const
{
    return attributes;
}

} // namespace Glue
