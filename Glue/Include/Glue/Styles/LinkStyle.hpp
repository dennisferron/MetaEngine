#pragma once

namespace Glue {

    enum class JointType
    {
        none
    };

    struct LinkStyle
    {
        JointType jointType = JointType::none;
    };

}
