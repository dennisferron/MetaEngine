#pragma once

namespace Glue { namespace Irrlicht {
    class MouseDragLinkAttribute;
    class IrrlichtAttribute;
}}

namespace Glue {

class IrrlichtMouseDrag
{
private:
    Irrlicht::MouseDragLinkAttribute* mouseAttr;
    Irrlicht::IrrlichtAttribute* irrAttr;

public:

    IrrlichtMouseDrag(
        Irrlicht::MouseDragLinkAttribute* mouseAttr,
        Irrlicht::IrrlichtAttribute* irrAttr);
    ~IrrlichtMouseDrag();
};

}
