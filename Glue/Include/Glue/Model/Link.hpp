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
    LinkStyle* style = nullptr;
    Node* fromNode = nullptr;
    Node* toNode = nullptr;
    Domain* domain = nullptr;
    Graph* graph = nullptr;

public:

    // This list is shared among all Link clones
    static std::vector<Interaction*> possibleInteractions;

    static void registerInteraction(Interaction*);

    Link(LinkStyle* newStyle);

    Link& setStyle(LinkStyle* value, Interaction* expectedInteraction);
    Link& setFromNode(Node* value);
    Link& setToNode(Node* value);
    Link& setGraph(Graph* value);
    Link& addAttribute(Attribute* attr, Interaction* expectedInteraction);

    Attribute* findAttribute(Attribute* attr);
};

}
