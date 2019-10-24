#pragma once

#include "Glue/Model/Node.hpp"
#include "Glue/Model/Domain.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Interactions/Link/LinkInteraction.hpp"

#include <vector>

namespace Glue {

class Link : public Domain
{
private:
    LinkStyle* style;
    Node* fromNode;
    Node* toNode;
    Domain domain;
    Graph* graph;

public:

    // This list is shared among all Link clones
    static std::vector<LinkInteraction*> possibleInteractions;

    static void registerInteraction(LinkInteraction* interaction);

    Link(LinkStyle* newStyle);

    Link& setStyle(LinkStyle* value, LinkInteraction* expectedInteraction);
    Link& setFromNode(Node* value);
    Link& setToNode(Node* value);
    Link& setGraph(Graph* value);
    Link& addAttribute(Object* attr, LinkInteraction* expectedInteraction);

    Object* findAttribute(Object* attr);
};

}
