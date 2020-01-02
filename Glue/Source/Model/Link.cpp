#include "Glue/Model/Link.hpp"
#include "Glue/Model/Node.hpp"
#include "Glue/Model/Graph.hpp"

namespace Glue {

std::vector<LinkInteraction*> Link::possibleInteractions;

Link::Link(Graph* graph, LinkStyle const& style, Node* fromNode, Node* toNode) :
    graph(graph),
    style(style),
    fromNode(fromNode),
    toNode(toNode)
{
}

void Link::registerInteraction(LinkInteraction* interaction)
{
    possibleInteractions.push_back(interaction);
}

Link& Link::addAttribute(Object* attr, LinkInteraction* expectedInteraction)
{
    throw "TODO:  implement domain.addObject for attribute here";
    //domain.addObject("link", attr/*, expectedInteraction*/);
    return *this;
}

Object* Link::findAttribute(Object* attr)
{
    throw "TODO:  implement domain.findObject";
    //return domain.findObject("link", attr);
}

} // namespace Glue
