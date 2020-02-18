#include "Glue/Bullet/ConstraintObj.hpp"

namespace Glue::Bullet
{

    ConstraintObj::ConstraintObj(
        LinkStyle style,
        std::unique_ptr<btTypedConstraint>&& constraint,
        IBulletAttribute* attrA,
        IBulletAttribute* attrB) :
            style(style),
            constraint(std::move(constraint)),
            attrA(attrA),
            attrB(attrB)
    {
    }

    LinkStyle const& ConstraintObj::get_style() const
    {
        return style;
    }

    btTypedConstraint* ConstraintObj::get_constraint() const
    {
        return constraint.get();
    }

    IBulletAttribute* ConstraintObj::get_attrA() const
    {
        return attrA;
    }

    IBulletAttribute* ConstraintObj::get_attrB() const
    {
        return attrB;
    }
}

