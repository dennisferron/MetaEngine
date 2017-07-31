#pragma once

#include <memory>

namespace Glue { namespace Avatar {

class NodeAttribute
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    NodeAttribute();
    ~NodeAttribute();

    bool canJump();
    void dive();
    void jump();
    void right();
    void left();
};

}}
