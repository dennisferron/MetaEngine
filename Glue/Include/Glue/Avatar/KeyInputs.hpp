#pragma once

#include <memory>

#include "irrlicht.h"

namespace Glue {
    class Node;
}

namespace Glue { namespace Avatar {

class KeyInputs
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    KeyInputs();
    ~KeyInputs();
    void update(Node* player, irr::IEventReceiver* events);
};

}}
