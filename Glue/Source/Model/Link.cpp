#include "Glue/Model/Link.hpp"
#include "Glue/Model/Node.hpp"
#include "Glue/Model/Graph.hpp"

namespace Glue {

std::vector<Interaction*> Link::possibleInteractions;

Link::Link(LinkStyle* newStyle) :
    style(newStyle),
    fromNode(nullptr),
    toNode(nullptr),
    domain(),
    graph(nullptr)
{
    throw "TODO: Implement domain.setSite for this";
    //domain.setSite(this);
}

void Link::registerInteraction(Interaction* interaction)
{
    possibleInteractions.push_back(interaction);
}

Link& Link::setStyle(LinkStyle* value, Interaction* expectedInteraction)
{
    style = value;
    throw "TODO:  implement domain.addObject for this";
    //domain.addObject("style", value, expectedInteraction);
    return *this;
}

Link& Link::setFromNode(Node* value)
{
    fromNode = value;

    // TODO:  Notify and remove old node value from domain.

    // TODO:  What does this do?
    if (fromNode != nullptr)
        domain.merge("fromNode", fromNode->domain, "node");

    return *this;
}

Link& Link::setToNode(Node* value)
{
    toNode = value;

    // TODO:  Notify and remove old node value from domain.

    // TODO:  What does this do?
    if (toNode != nullptr)
        domain.merge("toNode", toNode->domain, "node");

    return *this;
}

Link& Link::setGraph(Graph* value)
{
    graph = value;

    // TODO:  Notify and remove old components from the domain.

    throw "TODO:  Implement domain merge for component here";
    //domain.merge("component", graph->domain, "component");
    return *this;
}

Link& Link::addAttribute(Attribute* attr, Interaction* expectedInteraction)
{
    throw "TODO:  implement domain.addObject for attribute here";
    //domain.addObject("link", attr, expectedInteraction);
    return *this;
}

Attribute* Link::findAttribute(Attribute* attr)
{
    throw "TODO:  implement domain.findObject";
    //return domain.findObject("link", attr);
}

} // namespace Glue
