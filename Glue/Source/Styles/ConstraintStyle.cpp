#include "ConstraintStyle.hpp"

namespace Glue {

ConstraintStyle::ConstraintStyle()
    : LinkStyle(LinkTypes::none)
{
    jointType = JointTypes::none;

    // Set to true if you don't want the joined bodies to collide.
    disableLinkedBodyCollisions = false;

    // how big to draw the constraint debug wireframe
    debugDrawSize = 1.0
}

}