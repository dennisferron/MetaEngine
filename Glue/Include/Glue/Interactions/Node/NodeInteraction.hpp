#pragma once


#include <memory>

namespace Glue {

class NodeInteraction
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    NodeInteraction();

};

}
