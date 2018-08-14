#pragma once

#include "Glue/Constants.hpp"
#include "LinkStyle.hpp"
#include "MountStyle.hpp"

#include "irrlicht.h"

#include <experimental/optional>

namespace std {
    template <typename T>
    using optional = std::experimental::optional<T>;
}

namespace Glue {

    using SColor = irr::video::SColor;
    using ITexture = irr::video::ITexture;
    using IMesh = irr::scene::IMesh;

    enum class JointTypes
    {
        none,
        slider,
        coneTwist,
        hinge,
        gear,
        point2point,
        generic,
        genericSpring,
        disableCollision
    };

    struct ConstraintStyle : LinkStyle
    {
    protected:

        ConstraintStyle(JointTypes jointType);

    public:

        // Mount styles.  If the constraint is mounted "to the world" then set mountA to nil.
        std::optional<MountStyle> mountA;
        MountStyle mountB;

        JointTypes jointType;

        std::optional<Scalar> damping;

        // Set to true if you don't want the joined bodies to collide.
        bool disableLinkedBodyCollisions;

        // how big to draw the constraint debug wireframe
        Scalar debugDrawSize;
    };
}
