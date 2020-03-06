#include "Glue/Model/Link.hpp"
#include "Glue/Model/Node.hpp"
#include "Glue/Model/Graph.hpp"

namespace Glue {

Link::Link(LinkStyle const& style, INode* fromNode, INode* toNode) :
    style(style),
    fromNode(fromNode),
    toNode(toNode)
{
}

LinkStyle const& Link::get_style() const
{
    return style;
}

INode* Link::get_fromNode() const
{
    return fromNode;
}

INode* Link::get_toNode() const
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
