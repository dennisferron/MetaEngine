#pragma once

namespace Glue { namespace Irrlicht {
    class MouseDragLinkAttribute;
    class NodeAttribute;
}}

namespace Glue {

class IrrlichtMouseDrag
{
private:
    Irrlicht::MouseDragLinkAttribute* mouseAttr;
    Irrlicht::NodeAttribute* irrAttr;

public:

    IrrlichtMouseDrag(
        Irrlicht::MouseDragLinkAttribute* mouseAttr,
        Irrlicht::NodeAttribute* irrAttr);
    ~IrrlichtMouseDrag();
};

}
