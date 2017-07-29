#pragma once

#include <functional>

namespace Glue { namespace Irrlicht {
    class Node;
}}

namespace Glue {

struct MouseDragLinkAttribute
{
    std::function<void(Node*)> onDrag;
};

}
