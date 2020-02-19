#pragma once

#include "Glue/Model/Node.hpp"
#include "Glue/Styles/LinkStyle.hpp"

#include <vector>

namespace Glue {

class Link
{
private:
    Graph* graph;
    LinkStyle style;
    INode* fromNode;
    INode* toNode;

public:
    Link(Graph* graph, LinkStyle const& style, Node* fromNode, Node* toNode);

    Link& addAttribute(Object* attr);

    Object* findAttribute(Object* attr);
};

}
