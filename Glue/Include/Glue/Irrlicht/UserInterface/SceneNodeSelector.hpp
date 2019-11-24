#pragma once

#include <memory>

namespace Glue::Irrlicht {
    class IrrlichtAttribute;
}

namespace Glue { namespace Irrlicht {

class SceneNodeSelector
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    SceneNodeSelector();
    ~SceneNodeSelector();

    void select(IrrlichtAttribute* attr);
    void deselect(IrrlichtAttribute* attr);
};

}}
