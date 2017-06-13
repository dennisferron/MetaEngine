#pragma once

#include "Domain.hpp"

#include <vector>

namespace Glue {

class Graph;
class GameObjStyle;
class Interaction;

class NodeAttribute
{
};

class Node
{
private:
    Graph* graph = nullptr;
    GameObjStyle* style = nullptr;
    Domain* domain = nullptr;

    // This list is shared among all Node clones
    static std::vector<Interaction*> possibleInteractions;

public:

    Node(GameObjStyle style);
    ~Node();

    Node& setGraph(Graph* value);
    static void registerInteraction(Interaction* interaction);
    Node& addAttribute(NodeAttribute* attr, Interation* expectedInteraction);

    template <typename T>
    T* findAttribute() const
    {
        return domain->findObject<T>(DomainObjects::node);
    )
};

}
