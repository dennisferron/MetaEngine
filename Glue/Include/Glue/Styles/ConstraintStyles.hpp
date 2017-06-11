#pragma once

#include "ConstraintStyle.hpp"

namespace Glue::ConstraintStyles {

    struct SliderStyle : ConstraintStyle
    {
        SliderStyle();

        Scalar lowerLinLimit = 0;
        Scalar upperLinLimit = 0;
        Scalar lowerAngLimit = 0;
        Scalar upperAngLimit = 0;

        SliderStyle& setLinRange(Scalar lower, Scalar upper);
        SliderStyle& setAngRange(Scalar lower, Scalar upper);

        // I'm not really sure what this does, but some code I saw had a comment that seemed to say:
        // If true, use the frame in A as the reference frame for linear limits.
        // If false, use the frame in B as the reference frame for linear limits.
        // Now, what if we're using the B-only form of the constraint, then what does it mean if this is true??
        bool useLinearReferenceFrameA = true;
    };

    struct ConeTwistStyle : ConstraintStyle
    {
        ConeTwistStyle();

        Scalar swingSpan1 = TAU * 0.10;
        Scalar swingSpan2 = TAU * 0.10;
        Scalar twistSpan = TAU * 0.25;
        Scalar softness = 0.8;
        Scalar biasFactor = 0.3;
        Scalar relaxationFactor = 1.0;
    };

    struct HingeStyle : ConstraintStyle
    {
        HingeStyle();

        Scalar softness = 0.8;
        Scalar biasFactor = 0.3;
        Scalar relaxationFactor = 1.0;

        Scalar lowerAngLimit = 0;
        Scalar upperAngLimit = 0;
        HingeStyle& setAngRange(Scalar lower, Scalar upper);
        bool useLinearReferenceFrameA = false;
    };

    struct GearStyle : ConstraintStyle
    {
        GearStyle();
        Scalar ratio = 1.0;
    )

    struct Point2PointStyle : ConstraintStyle
    {
        Point2PointStyle();
    };

    struct Generic6DOFStyle : ConstraintStyle
    {
    protected:
        Generic6DOFStyle(JointTypes jointType);

    public:
        Generic6DOFStyle();

        lowerLinLimitX = 0;
        upperLinLimitX = 0;
        lowerAngLimitX = 0;
        upperAngLimitX = 0;

        lowerLinLimitY = 0;
        upperLinLimitY = 0;
        lowerAngLimitY = 0;
        upperAngLimitY = 0;

        lowerLinLimitZ = 0;
        upperLinLimitZ = 0;
        lowerAngLimitZ = 0;
        upperAngLimitZ = 0;

        Generic6DOFStyle& setLinRange(Scalar lowerX, Scalar upperX, Scalar lowerY, Scalar upperY, Scalar lowerZ, Scalar upperZ);
        Generic6DOFStyle& setAngRange(Scalar lowerX, Scalar upperX, Scalar lowerY, Scalar upperY, Scalar lowerZ, Scalar upperZ);

        bool useLinearReferenceFrameA = true;
    };

    struct SpringProperty
    {
        bool enabled = true;
        Scalar stiffness = 5;
        Scalar damping = 0.9;
    };

    struct Generic6DOFSpringStyle : Generic6DOFStyle
    {
        Generic6DOFSpringStyle();

        SpringProperty transX;
        SpringProperty transY;
        SpringProperty transZ;
        SpringProperty rotX;
        SpringProperty rotY;
        SpringProperty rotZ;
    };

    // A "constraint" with no limitations, so it disables collisions
    // between the linked bodies without constraining their motion.
    struct DisableCollisionStyle : Generic6DOFStyle
    {
        DisableCollisionStyle();
    };
}
