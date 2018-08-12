#pragma once

#include "Domain.hpp"

#include <vector>

namespace Glue {

class Graph;
class LinkStyle;
class Node;
class Interaction;
class Attribute;

class Link
{
private:
    LinkStyle* style;
    Node* fromNode;
    Node* toNode;
    Domain domain;
    Graph* graph;

public:

    // This list is shared among all Link clones
    static std::vector<Interaction*> possibleInteractions;

    static void registerInteraction(Interaction* interaction);

    Link(LinkStyle* newStyle);

    Link& setStyle(LinkStyle* value, Interaction* expectedInteraction);
    Link& setFromNode(Node* value);
    Link& setToNode(Node* value);
    Link& setGraph(Graph* value);
    Link& addAttribute(Attribute* attr, Interaction* expectedInteraction);

    Attribute* findAttribute(Attribute* attr);
};

}
