#pragma once

#include <BulletDynamics/ConstraintSolver/btTypedConstraint.h>
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Bullet/BulletAttribute.hpp"

namespace Glue::Bullet
{
    class Mount
    {

    };

struct ConstraintObj
{
    LinkStyle style;
    //Mount objA;
    //Mount objB;

    btTypedConstraint* constraint;
    BulletAttribute* attrA;
    BulletAttribute* attrB;
};

}
