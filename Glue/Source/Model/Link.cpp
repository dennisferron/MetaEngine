#include "Glue/Model/Link.hpp"
#include "Glue/Model/Node.hpp"
#include "Glue/Model/Graph.hpp"

namespace Glue
{

    Link::Link(
            Node* fromNode,
            Node* toNode,
            btTypedConstraint* constraint
            ) :
            fromNode(fromNode),
            toNode(toNode),
            constraint(constraint)
    {

    }

    Node* Link::get_fromNode() const
    {
        return fromNode;
    }

    Node* Link::get_toNode() const
    {
        return toNode;
    }

    btTypedConstraint* Link::get_constraint() const
    {
        return constraint;
    }

} // namespace Glue
