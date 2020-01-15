#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "btRigidBody.h"
#include "btBulletCollisionCommon.h"

#include "Glue/Styles/GameObjStyle.hpp"
#include "btDynamicsWorld.h"
#include "btRigidBody.h"

#include <memory>

namespace Glue::Bullet
{
    /**
     * Create shapes and rigid bodies for style.
     */
    class BodyBuilder
    {
    public:
        /// Create shape based on style and optional display mesh.
        virtual btCollisionShape* createShape(
                NodeStyle const& style,
                irr::scene::IMesh* dispShapeMesh) const;

        /// Create construction info for rigidbody.
        virtual btRigidBody::btRigidBodyConstructionInfo
            createConstructionInfo(
                NodeStyle const& style,
                btCollisionShape* physShape) const;

        /// Add rigid body to world based on construction info.
        /// Applies final style settings which can only be done
        /// after adding the body to the dynamics world.
        virtual std::unique_ptr<btRigidBody> addToWorld(
                NodeStyle const& style,
                btDynamicsWorld* dynamicsWorld,
                btRigidBody::btRigidBodyConstructionInfo const& rbInfo) const;
    };

}
