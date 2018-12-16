#pragma once

#include <memory>

#include "Glue/Styles/GameObjStyle.hpp"

class btRigidBody;

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
