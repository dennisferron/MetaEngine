#pragma once

#include "Glue/Animators/MotionStateAnimator.hpp"
#include "Glue/Constants.hpp"

#include "Glue/Styles/Styles.hpp"
#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Styles/ConstraintStyle.hpp"

#include "btDynamicsWorld.h"
#include "btRigidBody.h"
#include "btIDebugDraw.h"
#include "btBulletCollisionCommon.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "BulletDynamics/ConstraintSolver/btTypedConstraint.h"
#include "btBulletDynamicsCommon.h"

#include "ISceneNode.h"

#include "Glue/Model/ModelInterfaces.hpp"

#include <functional>
#include <memory>

namespace Glue::Bullet
{
    class IConstraintObj;
    class INode;

    /**
     * Create shapes and rigid bodies for style.
     */
    class IBodyBuilder
    {
    public:
		virtual ~IBodyBuilder() {}
	
        /// Create shape based on style and optional display mesh.
        virtual btCollisionShape* createShape(
                NodeStyle const& style,
                irr::scene::IMesh* dispShapeMesh) const = 0;

        /// Create construction info for rigidbody.
        virtual btRigidBody::btRigidBodyConstructionInfo
            createConstructionInfo(
                NodeStyle const& style,
                btCollisionShape* physShape) const = 0;

        /// Add rigid body to world based on construction info.
        /// Applies final style settings which can only be done
        /// after adding the body to the dynamics world.
        virtual std::unique_ptr<btRigidBody> addToWorld(
                NodeStyle const& style,
                btDynamicsWorld* dynamicsWorld,
                btRigidBody::btRigidBodyConstructionInfo const& rbInfo) const = 0;
    };

    class IBulletAttribute
    {
    public:

        ~IBulletAttribute() {}

        virtual btRigidBody* getRigidBody() const = 0;

        virtual void addConstraintA(IConstraintObj* constraint) = 0;

        virtual void addConstraintB(IConstraintObj* constraint) = 0;

        virtual void removeConstraintA(IConstraintObj* constraint) = 0;

        virtual void removeConstraintB(IConstraintObj* constraint) = 0;

        virtual void setLinearVelocity(Scalar xv, Scalar yv, Scalar zv) = 0;

        virtual void setAngularVelocity(Scalar xv, Scalar yv, Scalar zv) = 0;

        virtual btVector3 getAngularVelocity() const = 0;

        virtual btVector3 getLinearVelocity() const = 0;

        virtual void addChild(INode* otherObj) = 0;

        virtual void disableSleepState() = 0;

        virtual Scalar getRotZ() const = 0;

        virtual btVector3 getPos() const = 0;

        virtual void triggerAllGenerators(std::function<void(INode*)> onTrigger) = 0;

        virtual void lockTo(IBulletAttribute* otherObj) = 0;

        virtual void applyForceTowards(btVector3 const& targetPos, Scalar scalar, Scalar maxForce) = 0;

        virtual void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                              Scalar scalar, Scalar maxForce, Scalar maxVerticalForce) = 0;

        virtual void applyScaledForce(Scalar xforce, Scalar yforce, Scalar zforce,
                              Scalar scalar, Scalar maxForce) = 0;

        virtual void applyCentralForce(Scalar x, Scalar y, Scalar z) = 0;

        virtual void applyCentralImpulse(Scalar x, Scalar y, Scalar z) = 0;

        virtual void applyTorque(Scalar x, Scalar y, Scalar z) = 0;

        virtual void applyTorqueImpulse(Scalar x, Scalar y, Scalar z) = 0;

        // TODO:  add visited/removed.
        virtual void fallApart() = 0;
        virtual void structureDoForEachObject(
                std::function<void(IBulletAttribute*)> code) = 0;

        virtual void fallApart(
                std::vector<IBulletAttribute*>& visited,
                std::vector<IConstraintObj*>& removed) = 0;

        virtual void structureDoForEachObject(
                std::function<void(IBulletAttribute*)> code,
                std::vector<IBulletAttribute*>& visited) = 0;
    };


    class IConstraintObj
    {
    public:
        virtual ~IConstraintObj() {}

        virtual LinkStyle const& get_style() const = 0;
        virtual btTypedConstraint* get_constraint() const = 0;
        virtual IBulletAttribute* get_attrA() const = 0;
        virtual IBulletAttribute* get_attrB() const = 0;
    };

	class IConstraintBuilder
	{
	public:
		virtual ~IConstraintBuilder() {}
        virtual IConstraintObj* create(ConstraintStyle const& style, btRigidBody* objA, btRigidBody* objB) = 0;
	};

	using TickHandler = std::function<void(btDynamicsWorld*,btScalar)>;

	class IScriptedWorldManager
	{
	public:
		virtual ~IScriptedWorldManager() {}
		virtual void setOnTick(btDynamicsWorld& world, TickHandler onTick_) = 0;
		virtual void setOnPreTick(btDynamicsWorld& world, TickHandler onPreTick_) = 0;
	};

    /**
     * The BulletComponent synchronizes the btDynamicsWorld to the Graph.
     *
     * It associates a BulletAttribute to each graph-level node
     * and a ConstraintObj to each graph-level link.  It also implements
     * time-based events for the physics engine.
     */
    class IBulletComponent
    {
    public:
        virtual ~IBulletComponent() {};

        /// Turns debug drawing on and off
        virtual void setDebugMode(bool debugMode) = 0;

        /// Converts a link to a constraint if jointType is set.
        /// The Glue::Link combines a style with two endpoints.
        virtual void addLink(Glue::ILink* link) = 0;

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
        virtual void removeConstraint(IConstraintObj* constraint) = 0;

        /// Creates a ConstraintObj based on the @style.
        /// Add a constraint to the btDynamicsWorld.
        virtual IConstraintObj* addConstraint(ConstraintStyle const& style, IBulletAttribute* attrA, IBulletAttribute* attrB) = 0;

        /// Creates a BulletAttribute based on the style of the @node.
        /// Adds a btRigidBody to the btDynamicsWorld.
        virtual IBulletAttribute* addNode(INode* node) = 0;

        // TODO:  Implement this
        //virtual void removeNode(Node* node) = 0;
    };

}
