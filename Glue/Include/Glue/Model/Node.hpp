#pragma once

#include "Glue/Model/Domain.hpp"
#include "Glue/Interactions/Node/NodeInteraction.hpp"
#include "Glue/Styles/GameObjStyle.hpp"

#include "Glue/Irrlicht/IrrlichtAttribute.hpp"

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
    GameObjStyle style;
    Domain* domain;

    // This list is shared among all Link clones
    static std::vector<NodeInteraction*> possibleInteractions;

    static void registerInteraction(NodeInteraction* interaction);

private:

    Glue::Irrlicht::IrrlichtAttribute* irrlicht_attribute = nullptr;

public:

    Node(GameObjStyle const& style);
    ~Node();

    Node& setGraph(Graph* value);
    Node& addAttribute(NodeAttribute* attr, NodeInteraction* expectedInteraction);

    void addAttribute(Glue::Irrlicht::IrrlichtAttribute* attr);

    /*
    template <typename T>
    T* findAttribute() const
    {
        return domain->findObject<T>(DomainObjects::node);
    )
    */
};

}
