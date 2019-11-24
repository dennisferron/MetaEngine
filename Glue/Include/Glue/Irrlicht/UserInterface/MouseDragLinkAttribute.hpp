#pragma once

#include <functional>

#include "Glue/Irrlicht/IrrlichtAttribute.hpp"

namespace Glue {

struct MouseDragLinkAttribute
{
    std::function<void(Irrlicht::IrrlichtAttribute*)> onDrag;
};

}
