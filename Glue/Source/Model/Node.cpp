#include "Model/Node.cpp"

namespace Glue {

// This list is shared among all Node clones
std::vector<Interaction*> Node::possibleInteractions;

Node::Node(GameObjStyle const* style) :
    graph(nullptr),
    style(style),
    domain()
{
    domain.setSite(this);
}

Node::~Node()
{
}

Node& Node::setGraph(Graph* value)
{
    graph = value;
    for (auto& c : components)
        domain.addObject("component", c);
}

void Node::registerInteraction(Interaction* interaction)
{
    possibleInteractions.push_back(interaction);
}

Node& addAttribute(NodeAttribute* attr, Interation* expectedInteraction)
{
    domain.addObject("node", attr, expectedInteraction);
}

} // namespace Glue
