#include "Glue/Styles/ConstraintStyles.hpp"

using namespace Glue::Constants;

namespace Glue::ConstraintStyles
{

    SliderStyle::SliderStyle()
    {
        lowerLinLimit = 0;
        upperLinLimit = 0;
        lowerAngLimit = 0;
        upperAngLimit = 0;

        // I'm not really sure what this does, but some code I saw had a comment that seemed to say:
        // If true, use the frame in A as the reference frame for linear limits.
        // If false, use the frame in B as the reference frame for linear limits.
        // Now, what if we're using the B-only form of the constraint, then what does it mean if this is true??
        useLinearReferenceFrameA = true;
    }

    SliderStyle& SliderStyle::setLinRange(Scalar lower, Scalar upper)
    {
        lowerLinLimit = lower;
        upperLinLimit = upper;
        return *this;
    }

    SliderStyle& SliderStyle::setAngRange(Scalar lower, Scalar upper)
    {
        lowerAngLimit = lower;
        upperAngLimit = upper;
        return *this;
    }

    ConeTwistStyle::ConeTwistStyle()
    {
        swingSpan1 = TAU * 0.10;
        swingSpan2 = TAU * 0.10;
        twistSpan = TAU * 0.25;
        softness = 0.8;
        biasFactor = 0.3;
        relaxationFactor = 1.0;
    }

    HingeStyle::HingeStyle()
    {
        softness = 0.8;
        biasFactor = 0.3;
        relaxationFactor = 1.0;
        lowerAngLimit = 0;
        upperAngLimit = 0;
        useLinearReferenceFrameA = false;
    }

    HingeStyle& HingeStyle::setAngRange(Scalar lower, Scalar upper)
    {
        lowerAngLimit = lower;
        upperAngLimit = upper;
        return *this;
    }

    GearStyle::GearStyle()
    {
        ratio = 1.0;
    }

    Point2PointStyle::Point2PointStyle()
    {
    }

    Generic6DOFStyle::Generic6DOFStyle()
    {
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

        useLinearReferenceFrameA = true;
    }

    Generic6DOFStyle&
    Generic6DOFStyle::setLinRange(Scalar lowerX, Scalar upperX, Scalar lowerY, Scalar upperY, Scalar lowerZ,
                                  Scalar upperZ)
    {
        lowerLinLimitX = lowerX;
        upperLinLimitX = upperX;

        lowerLinLimitY = lowerY;
        upperLinLimitY = upperY;

        lowerLinLimitZ = lowerZ;
        upperLinLimitZ = upperZ;

        return *this;
    }

    Generic6DOFStyle&
    Generic6DOFStyle::setAngRange(Scalar lowerX, Scalar upperX, Scalar lowerY, Scalar upperY, Scalar lowerZ,
                                  Scalar upperZ)
    {
        lowerAngLimitX = lowerX;
        upperAngLimitX = upperX;

        lowerAngLimitY = lowerY;
        upperAngLimitY = upperY;

        lowerAngLimitZ = lowerZ;
        upperAngLimitZ = upperZ;

        return *this;
    }

    SpringProperty::SpringProperty()
    {
        enabled = true;
        stiffness = 5;
        damping = 0.9;
    }

    Generic6DOFSpringStyle::Generic6DOFSpringStyle()
    {
        // Default ranges so you know it's a spring
        setLinRange(-0.1, 0.1, -0.1, 0.1, -0.1, 0.1);
        setAngRange(-TAU / 10, TAU / 10, -TAU / 10, TAU / 10, -TAU / 10, TAU / 10);
    }
}
