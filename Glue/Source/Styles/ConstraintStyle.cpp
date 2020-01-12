#include "Glue/Styles/ConstraintStyle.hpp"

namespace Glue {

ConstraintStyle::ConstraintStyle()
{
    // Set to true if you don't want the joined bodies to collide.
    disableLinkedBodyCollisions = false;

    // how big to draw the constraint debug wireframe
    debugDrawSize = 1.0;
}

}