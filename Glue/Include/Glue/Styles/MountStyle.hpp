#pragma once

namespace Glue {

    // Constraints have one or two mount points.
    struct MountStyle
    {
        // Location (relative to the rigid body)
        float x = 0;
        float y = 0;
        float z = 0;

        // Set x,y,z all at once
        MountStyle& setPos(float x, float y, float z);

        // Set one or the other of the following two rotation styles but not both.
        // Yaw, Roll, Pitch are used iff axisX==axisY==axisZ==0.

        // Rotation by axis and angle (better for first person view? might be useful for space ship game -?)
        float axisX = 0;
        float axisY = 0;
        float axisZ = 0;
        float angle = 0;

        MountStyle& setAxis(x, y, z);

        // Rotation by yaw, pitch, roll (better if your frame of reference is outside the object -?)
        float yaw = 0;
        float pitch = 0;
        float roll = 0;
    )
)
