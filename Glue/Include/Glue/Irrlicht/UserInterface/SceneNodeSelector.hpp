#pragma once

#include <memory>

namespace Glue {
    class Attribute;
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

    void select(Attribute* attr);
    void deselect(Attribute* attr);
};

}}
