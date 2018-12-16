#pragma once

#include "Glue/Constants.hpp"

namespace Glue {

    // Constraints have one or two mount points.
    struct MountStyle
    {
        MountStyle(Scalar x, Scalar y, Scalar z);

        // Location (relative to the rigid body)
        Scalar x = 0;
        Scalar y = 0;
        Scalar z = 0;

        // Set x,y,z all at once
        MountStyle& setPos(Scalar x, Scalar y, Scalar z);

        // Set one or the other of the following two rotation styles but not both.
        // Yaw, Roll, Pitch are used iff axisX==axisY==axisZ==0.

        // Rotation by axis and angle (better for first person view? might be useful for space ship game -?)
        Scalar axisX = 0;
        Scalar axisY = 0;
        Scalar axisZ = 0;
        Scalar angle = 0;

        MountStyle& setAxis(Scalar x, Scalar y, Scalar z);

        // Rotation by yaw, pitch, roll (better if your frame of reference is outside the object -?)
        Scalar yaw = 0;
        Scalar pitch = 0;
        Scalar roll = 0;
    };
}
