#include "Model/Link.hpp"

namespace Glue {

std::vector<Interaction*> Link::possibleInteractions;

Link::Link(LinkStyle* newStyle) :
    style(newStyle),
    fromNode(nullptr),
    toNode(nullptr),
    domain(),
    graph(nullptr)
{
    domain.setSite(this);
}

void Link::registerInteraction(Interaction* interaction)
{
    possibleInteractions.push_back(interaction);
}

Link& Link::setStyle(LinkStyle* value, Interaction* expectedInteraction)
{
    style = value;
    domain.addObject("style", value, expectedInteraction);
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

    domain.merge("component", graph->domain, "component");
    return *this;
}

Link& Link::addAttribute(Attribute* attr, Interaction* expectedInteraction)
{
    domain.addObject("link", attr, expectedInteraction);
    return *this;
}

Attribute* Link::findAttribute(Attribute* attr)
{
    return domain.findObject("link", attr);
}

} // namespace Glue
