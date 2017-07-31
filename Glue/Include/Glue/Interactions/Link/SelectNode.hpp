#pragma once

namespace Glue { namespace Irrlicht {
    class NodeAttribute;
    class SceneNodeSelector;
}}

namespace Glue {

class SelectNode
{
private:
    Irrlicht::SceneNodeSelector* selector;
    Irrlicht::NodeAttribute* dispAttr;

public:

    SelectNode(Irrlicht::SceneNodeSelector* selector,
               Irrlicht::NodeAttribute* dispAttr);
    ~SelectNode();
};

}
