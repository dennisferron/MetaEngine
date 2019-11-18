#pragma once

#include "Glue/Model/Domain.hpp"
#include "Glue/Interactions/Node/NodeInteraction.hpp"
#include "Glue/Styles/GameObjStyle.hpp"

#include <vector>

namespace Glue {

class Graph;
class Interaction;

class NodeAttribute
{
};

class Node
{


public:
    Graph* graph;
    GameObjStyle const* style;
    Domain* domain;

    // This list is shared among all Link clones
    static std::vector<NodeInteraction*> possibleInteractions;

    static void registerInteraction(NodeInteraction* interaction);

public:

    Node(GameObjStyle const* style);
    ~Node();

    Node& setGraph(Graph* value);
    Node& addAttribute(NodeAttribute* attr, NodeInteraction* expectedInteraction);

    /*
    template <typename T>
    T* findAttribute() const
    {
        return domain->findObject<T>(DomainObjects::node);
    )
    */
};

}
