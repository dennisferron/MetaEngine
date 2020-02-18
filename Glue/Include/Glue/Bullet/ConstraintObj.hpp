#pragma once

#include "BulletDynamics/ConstraintSolver/btTypedConstraint.h"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Bullet/BulletInterfaces.hpp"

#include <memory>

namespace Glue::Bullet
{
    class ConstraintObj : public IConstraintObj
    {
    private:
        LinkStyle style;
        std::unique_ptr<btTypedConstraint> constraint;
        IBulletAttribute* attrA;
        IBulletAttribute* attrB;

    public:
        ConstraintObj(
            LinkStyle style,
            std::unique_ptr<btTypedConstraint>&& constraint,
            IBulletAttribute* attrA,
            IBulletAttribute* attrB);

        LinkStyle const& get_style() const;
        btTypedConstraint* get_constraint() const;
        IBulletAttribute* get_attrA() const;
        IBulletAttribute* get_attrB() const;
    };

}
