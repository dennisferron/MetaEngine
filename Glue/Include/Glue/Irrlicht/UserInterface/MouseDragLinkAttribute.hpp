#pragma once

#include <functional>

#include "Glue/Irrlicht/NodeAttribute.hpp"

namespace Glue {

struct MouseDragLinkAttribute
{
    std::function<void(Irrlicht::NodeAttribute*)> onDrag;
};

}
