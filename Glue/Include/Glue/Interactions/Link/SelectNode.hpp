#pragma once

namespace Glue { namespace Irrlicht {
    class IrrlichtAttribute;
    class SceneNodeSelector;
}}

namespace Glue {

class SelectNode
{
private:
    Irrlicht::SceneNodeSelector* selector;
    Irrlicht::IrrlichtAttribute* dispAttr;

public:

    SelectNode(Irrlicht::SceneNodeSelector* selector,
               Irrlicht::IrrlichtAttribute* dispAttr);
    ~SelectNode();
};

}
