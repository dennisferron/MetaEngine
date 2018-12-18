#include "Glue/Model/Node.hpp"

#include <vector>

namespace Glue {

// This list is shared among all Node clones
std::vector<Interaction*> Node::possibleInteractions;

Node::Node(GameObjStyle const* style) :
    graph(nullptr),
    style(style),
    domain()
{
    throw "TODO: implement domain.setSite";
    //domain.setSite(this);
}

Node::~Node()
{
}

Node& Node::setGraph(Graph* value)
{
    throw "TODO:  implement domain.addObject";
//    graph = value;
//    for (auto& c : components)
//        domain.addObject("component", c);
}

void Node::registerInteraction(Interaction* interaction)
{
    possibleInteractions.push_back(interaction);
}

Node& Node::addAttribute(NodeAttribute* attr, Interaction* expectedInteraction)
{
    throw "TODO: implement domain.addObject";
    //domain.addObject("node", attr, expectedInteraction);
}

} // namespace Glue
