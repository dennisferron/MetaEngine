#include "Glue/Styles/LinkStyles.hpp"

namespace Glue namespace LinkStyles {

LookAtStyle : public LinkStyle
{
    LookAtStyle()
        : LinkStyle(JointType::lookAt)
    {
    }
};

struct MouseDragStyle : public LinkStyle
{
    MouseDragStyle()
        : LinkStyle(JointType::mouseDrag)
    {
    }
};

}}
