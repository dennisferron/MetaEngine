#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "btRigidBody.h"
#include "btBulletCollisionCommon.h"

#include "Glue/Styles/GameObjStyle.hpp"
#include "btDynamicsWorld.h"
#include "btRigidBody.h"

namespace Glue::Bullet
{

    class BodyBuilder
    {
    public:
        btCollisionShape* createShape(
                NodeStyle const& style,
                irr::scene::IMesh* dispShapeMesh) const;

        btRigidBody::btRigidBodyConstructionInfo
            createConstructionInfo(
                NodeStyle const& style,
                btCollisionShape* physShape) const;

        btRigidBody* addToWorld(
                NodeStyle const& style,
                btDynamicsWorld* dynamicsWorld,
                btRigidBody::btRigidBodyConstructionInfo const& rbInfo) const;
    };

}
