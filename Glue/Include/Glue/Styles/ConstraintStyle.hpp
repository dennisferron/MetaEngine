#pragma once

#include "Glue/Styles/MountStyle.hpp"
#include "Glue/Styles/ConstraintStyles.hpp"

#include "irrlicht.h"

#include <optional>

namespace Glue
{
    using SColor = irr::video::SColor;
    using ITexture = irr::video::ITexture;
    using IMesh = irr::scene::IMesh;

    class ConstraintStyle
    {
    public:

        // Mount styles.  If the constraint is mounted "to the world" then set mountA to nil.
        std::optional<MountStyle> mountA;
        std::optional<MountStyle> mountB;

        SomeConstraintStyle jointType;

        std::optional<Scalar> damping;

        // Set to true if you don't want the joined bodies to collide.
        bool disableLinkedBodyCollisions;

        // how big to draw the constraint debug wireframe
        Scalar debugDrawSize;
    };
}
