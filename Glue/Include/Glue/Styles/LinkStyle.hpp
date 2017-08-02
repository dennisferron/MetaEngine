#pragma once

namespace Glue {

    enum class JointType
    {
        none,
        lookAt,
        mouseDrag,
        physConstraint
    };

    struct LinkStyle
    {
        JointType jointType;
        LinkStyle(JointType jointType = JointType::none);
    };

}
