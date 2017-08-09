#include "Glue/Styles/LinkStyles.hpp"

namespace Glue namespace LinkStyles {

LookAtStyle::LookAtStyle()
    : LinkStyle(JointType::lookAt)
{
}

MouseDragStyle::MouseDragStyle()
    : LinkStyle(JointType::mouseDrag)
{
}

}}
