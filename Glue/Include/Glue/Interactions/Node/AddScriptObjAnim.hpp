#pragma once

namespace Glue { namespace Irrlicht {
    class NodeAttribute;
}}

namespace Glue {

class AddScriptObjAnim
{
public:
    AddScriptObjAnim(Irrlicht::NodeAttribute* dispAttr);
    void enter();
};

}
