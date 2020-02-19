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

void Link::addAttribute(LinkAttribute attr)
{
    attributes.push_back(attr);
}

} // namespace Glue
