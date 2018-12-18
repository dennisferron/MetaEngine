#include "Glue/Styles/LinkStyles.hpp"

namespace Glue { namespace LinkStyles {

LookAtStyle::LookAtStyle()
    : LinkStyle(LinkTypes::lookAt)
{
}

MouseDragStyle::MouseDragStyle()
    : LinkStyle(LinkTypes::mouseDrag)
{
}

}}
