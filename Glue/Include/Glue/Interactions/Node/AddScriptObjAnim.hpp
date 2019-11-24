#pragma once

namespace Glue { namespace Irrlicht {
    class IrrlichtAttribute;
}}

namespace Glue {

class AddScriptObjAnim
{
public:
    AddScriptObjAnim(Irrlicht::IrrlichtAttribute* dispAttr);
    void enter();
};

}
