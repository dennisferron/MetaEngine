#include "ConstraintStyles.hpp"

namespace Glue { namespace ConstraintStyles {

SliderStyle::SliderStyle()
    : ConstraintStyle(JointTypes::slider)
{
    lowerLinLimit = 0;
    upperLinLimit = 0;
    lowerAngLimit = 0;
    upperAngLimit = 0;
    useLinearReferenceFrameA = true;
}

SliderStyle& SliderStyle::setLinRange(Scalar lower, Scalar upper)
{
    lowerLinLimit = lower;
    upperLinLimit = upper;
}

SliderStyle& SliderStyle::setAngRange(Scalar lower, Scalar upper)
{
    lowerAngLimit = lower;
    upperAngLimit = upper;
}

ConeTwistStyle::ConeTwistStyle()
    : ConstraintStyle(JointTypes::coneTwist)
{
    swingSpan1 = TAU * 0.10;
    swingSpan2 = TAU * 0.10;
    twistSpan = TAU * 0.25;
    softness = 0.8;
    biasFactor = 0.3;
    relaxationFactor = 1.0;
}

HingeStyle::HingeStyle()
    : ConstraintStyle(JointTypes::hinge)
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
}

GearStyle::GearStyle()
    : ConstraintStyle(JointTypes::gear)
{
    Scalar ratio = 1.0;
}

Point2PointStyle::Point2PointStyle()
    : ConstraintStyle(JointTypes::point2point)
{
}

Generic6DOFStyle::Generic6DOFStyle()
    : Generic6DOFStyle(JointTypes::generic)
{
}

Generic6DOFStyle::Generic6DOFStyle(JointTypes jointType)
    : ConstraintStyle(jointType)
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

Generic6DOFStyle& Generic6DOFStyle::setLinRange(Scalar lowerX, Scalar upperX, Scalar lowerY, Scalar upperY, Scalar lowerZ, Scalar upperZ)
{
    lowerLinLimitX = lowerX;
    upperLinLimitX = upperX;

    lowerLinLimitY = lowerY;
    upperLinLimitY = upperY;

    lowerLinLimitZ = lowerZ;
    upperLinLimitZ = upperZ;
}

Generic6DOFStyle& Generic6DOFStyle::setAngRange(Scalar lowerX, Scalar upperX, Scalar lowerY, Scalar upperY, Scalar lowerZ, Scalar upperZ)
{
    lowerAngLimitX = lowerX;
    upperAngLimitX = upperX;

    lowerAngLimitY = lowerY;
    upperAngLimitY = upperY;

    lowerAngLimitZ = lowerZ;
    upperAngLimitZ = upperZ;
}

SpringProperty::SpringProperty()
{
    enabled = true;
    stiffness = 5;
    damping = 0.9;
}

Generic6DOFSpringStyle::Generic6DOFSpringStyle()
    : Generic6DOFStyle(JointTypes::genericSpring)
{
    // Default ranges so you know it's a spring
    setLinRange(-0.1,0.1,  -0.1,0.1,  -0.1,0.1);
    setAngRange(-TAU/10,TAU/10,  -TAU/10,TAU/10,  -TAU/10,TAU/10);
}

DisableCollisionStyle::DisableCollisionStyle()
    : Generic6DOFStyle(JointTypes::disableCollision)
{
    disableLinkedBodyCollisions(true);
    setLinRange(1,0, 1,0, 1,0);
    setAngRange(1,0, 1,0, 1,0);
    debugDrawSize = 0;
}
