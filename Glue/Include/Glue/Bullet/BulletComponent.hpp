#pragma once

#include "Glue/Model/Component.hpp"

#include "Glue/Constants.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Bullet/BulletAttribute.hpp"
#include "Glue/Bullet/ConstraintObj.hpp"
#include "Glue/Model/Link.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Bullet/ScriptedWorldManager.hpp"

#include "btRigidBody.h"
#include "btIDebugDraw.h"

#include <functional>
#include <memory>


namespace Glue::Bullet
{
    /**
     * The BulletComponent synchronizes the btDynamicsWorld to the Graph.
     *
     * It associates a BulletAttribute to each graph-level node
     * and a ConstraintObj to each graph-level link.  It also implements
     * time-based events for the physics engine.
     */
    class BulletComponent : public Component
    {
    public:
        virtual ~BulletComponent() = 0;

        /// Turns debug drawing on and off
        virtual void setDebugMode(bool debugMode) = 0;

        /// Converts a link to a constraint if jointType is set.
        /// The Glue::Link combines a style with two endpoints.
        virtual void addLink(Glue::Link* link) = 0;

        /// Accepts an object to use to draw debug graphics.
        virtual void setDebugDrawer(btIDebugDraw* drawer) = 0;

        /// The passed function will be called on every physics tick.
        virtual void setOnTick(TickHandler aBlock) = 0;

        /// The passed function will be called on every physics pre-tick.
        virtual void setOnPreTick(TickHandler aBlock) = 0;

        /// The method called during the physics portion of a frame.
        /// It advances the btDynamicsWorld one frame.
        virtual void onPhysics(Scalar timeElapsed) = 0;

        /// The method called during the graphics portion of a frame.
        /// It draws debug graphics using the object passed to setDebugDrawer.
        virtual void onGraphics(Scalar timeElapsed) = 0;

        /// Remove a constraint from the btDynamicsWorld.
        virtual void removeConstraint(ConstraintObj* constraint) = 0;

        /// Creates a ConstraintObj based on the @style.
        /// Add a constraint to the btDynamicsWorld.
        virtual ConstraintObj* addConstraint(LinkStyle* style, btRigidBody &attrA, btRigidBody &attrB) = 0;

        /// Creates a BulletAttribute based on the style of the @node.
        /// Adds a btRigidBody to the btDynamicsWorld.
        virtual BulletAttribute* addNode(Node* node) = 0;
    };

}
