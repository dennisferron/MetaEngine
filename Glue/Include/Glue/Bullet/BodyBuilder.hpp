#pragma once

#include <memory>

namespace Glue { namespace Bullet {

class BodyBuilder
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    BodyBuilder();
    ~BodyBuilder();

    btRigidBody* buildBody(NodeStyle* style) const;
};

}}
