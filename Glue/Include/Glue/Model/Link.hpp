#pragma once

#include "Glue/Model/Node.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Interactions/Link/LinkInteraction.hpp"

#include <vector>

namespace Glue {

class Link
{
public:
    Graph* graph;
    LinkStyle style;
    Node* fromNode;
    Node* toNode;

    // This list is shared among all Link clones
    static std::vector<LinkInteraction*> possibleInteractions;

    static void registerInteraction(LinkInteraction* interaction);

    Link(Graph* graph, LinkStyle const& style, Node* fromNode, Node* toNode);

    Link& addAttribute(Object* attr, LinkInteraction* expectedInteraction);

    Object* findAttribute(Object* attr);
};

}
