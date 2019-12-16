#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Bullet/ShapeBuilder.hpp"
#include "btDynamicsWorld.h"
#include "btRigidBody.h"

namespace Glue { namespace Bullet {

class BodyBuilder
{
private:
    btDynamicsWorld* dynamicsWorld;
    ShapeBuilder* shapeBuilder;

public:
    BodyBuilder(btDynamicsWorld* dynamicsWorld, ShapeBuilder* shapeBuilder);

    btRigidBody* buildBody(NodeStyle const& style) const;
};

}}
