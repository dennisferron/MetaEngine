#pragma once

#include <memory>

namespace Glue {

class NodeInteraction : public Interaction
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    NodeInteraction();
};

}
