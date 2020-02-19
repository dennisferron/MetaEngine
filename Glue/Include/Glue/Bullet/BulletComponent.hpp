#pragma once

#include "Glue/Bullet/BulletInterfaces.hpp"
#include "Glue/Bullet/BodyBuilder.hpp"
#include "Glue/Bullet/ScriptedWorldManager.hpp"
#include "Glue/Bullet/ConstraintBuilder.hpp"

#include <BulletDynamics/ConstraintSolver/btConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletSoftBody/btSoftBody.h>
#include "BulletCollision/BroadphaseCollision/btDispatcher.h"
#include "BulletCollision/CollisionDispatch/btCollisionConfiguration.h"


namespace Glue::Bullet 
{
    class BulletComponent : public IBulletComponent
    {
    private:
        btScalar fixedTimeStep = 1.0 / 60.0;
        int subframes = 30;
        btCollisionConfiguration* collisionConfiguration;
        btDispatcher* dispatcher = nullptr;  // This is a bullet physics thing, not associated with UI event dispatch
        btBroadphaseInterface* broadphaseInterface = nullptr;
        btConstraintSolver* solver = nullptr;
        btDynamicsWorld* dynamicsWorld = nullptr;
        btSoftBodyWorldInfo softBodyWorldInfo;
        ScriptedWorldManager scriptWorldMgr;
        btIDebugDraw* debugDrawer;
        BodyBuilder* bodyBuilder = nullptr;
        ConstraintBuilder* constraintBuilder = nullptr;

    public:
        BulletComponent(BodyBuilder* bodyBuilder, ConstraintBuilder* constraintBuilder);

        ~BulletComponent() final;

        void setDebugMode(bool debugMode) final;

        void addLink(ILink* link) final;

        void setDebugDrawer(btIDebugDraw* drawer) final;

        void setOnTick(TickHandler aBlock) final;

        void setOnPreTick(TickHandler aBlock) final;

        void onPhysics(Scalar timeElapsed) final;

        void onGraphics(Scalar timeElapsed) final;

        void removeConstraint(IConstraintObj* constraint) final;

        IConstraintObj* addConstraint(ConstraintStyle const& style, IBulletAttribute* attrA, IBulletAttribute* attrB) final;

        IBulletAttribute* addNode(INode* node) final;
    };
}
