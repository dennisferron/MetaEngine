#pragma once

#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Styles/LinkStyle.hpp"

class btTypedConstraint;

namespace Glue
{
    class Link
    {
    private:
        Node* fromNode;  // aka attrA / nodeA
        Node* toNode;    // aka attrB / nodeB
        btTypedConstraint* constraint;

    public:
        Link(
            Node* fromNode,
            Node* toNode,
            btTypedConstraint* constraint
        );

        Node* get_fromNode() const;
        Node* get_toNode() const;
        btTypedConstraint* get_constraint() const;

    };

}
