#pragma once

#include <BulletDynamics/ConstraintSolver/btTypedConstraint.h>
#include "Glue/Styles/LinkStyle.hpp"

#include <memory>

namespace Glue::Bullet
{
    class BulletAttribute;

    class ConstraintObj
    {
    private:
        LinkStyle style;
        std::unique_ptr<btTypedConstraint> constraint;
        BulletAttribute* attrA;
        BulletAttribute* attrB;

    public:
        ConstraintObj(
            LinkStyle style,
            std::unique_ptr<btTypedConstraint>&& constraint,
            BulletAttribute* attrA,
            BulletAttribute* attrB);

        LinkStyle const& get_style() const;
        btTypedConstraint* get_constraint() const;
        BulletAttribute* get_attrA() const;
        BulletAttribute* get_attrB() const;
    };

}
