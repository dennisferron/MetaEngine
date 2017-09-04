#pragma once

#include "ConstraintStyle.hpp"

namespace Glue { namespace ConstraintStyles {

    struct SliderStyle : ConstraintStyle
    {
        SliderStyle();

        Scalar lowerLinLimit;
        Scalar upperLinLimit;
        Scalar lowerAngLimit;
        Scalar upperAngLimit;

        SliderStyle& setLinRange(Scalar lower, Scalar upper);
        SliderStyle& setAngRange(Scalar lower, Scalar upper);

        // I'm not really sure what this does, but some code I saw had a comment that seemed to say:
        // If true, use the frame in A as the reference frame for linear limits.
        // If false, use the frame in B as the reference frame for linear limits.
        // Now, what if we're using the B-only form of the constraint, then what does it mean if this is true??
        bool useLinearReferenceFrameA;
    };

    struct ConeTwistStyle : ConstraintStyle
    {
        ConeTwistStyle();

        Scalar swingSpan1;
        Scalar swingSpan2;
        Scalar twistSpan;
        Scalar softness;
        Scalar biasFactor;
        Scalar relaxationFactor;
    };

    struct HingeStyle : ConstraintStyle
    {
        HingeStyle();

        Scalar softness;
        Scalar biasFactor;
        Scalar relaxationFactor;

        Scalar lowerAngLimit;
        Scalar upperAngLimit;
        HingeStyle& setAngRange(Scalar lower, Scalar upper);
        bool useLinearReferenceFrameA;
    };

    struct GearStyle : ConstraintStyle
    {
        GearStyle();
        Scalar ratio;
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

        Scalar lowerLinLimitX;
        Scalar upperLinLimitX;
        Scalar lowerAngLimitX;
        Scalar upperAngLimitX;

        Scalar lowerLinLimitY;
        Scalar upperLinLimitY;
        Scalar lowerAngLimitY;
        Scalar upperAngLimitY;

        Scalar lowerLinLimitZ;
        Scalar upperLinLimitZ;
        Scalar lowerAngLimitZ;
        Scalar upperAngLimitZ;

        Generic6DOFStyle& setLinRange(Scalar lowerX, Scalar upperX, Scalar lowerY, Scalar upperY, Scalar lowerZ, Scalar upperZ);
        Generic6DOFStyle& setAngRange(Scalar lowerX, Scalar upperX, Scalar lowerY, Scalar upperY, Scalar lowerZ, Scalar upperZ);

        bool useLinearReferenceFrameA = true;
    };

    struct SpringProperty
    {
        SpringProperty();
        bool enabled;
        Scalar stiffness;
        Scalar damping;
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
}}
