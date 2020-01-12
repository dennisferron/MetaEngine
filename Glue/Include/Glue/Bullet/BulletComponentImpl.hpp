#pragma once

#include "Glue/Bullet/BulletComponent.hpp"
#include "Glue/Bullet/BodyBuilder.hpp"
#include "Glue/Bullet/ScriptedWorldManager.hpp"

#include <BulletDynamics/ConstraintSolver/btConstraintSolver.h>
#include <BulletDynamics/Dynamics/btDynamicsWorld.h>
#include <BulletSoftBody/btSoftBody.h>
#include "BulletCollision/BroadphaseCollision/btDispatcher.h"
#include "BulletCollision/CollisionDispatch/btCollisionConfiguration.h"
#include "ConstraintBuilder.hpp"


namespace Glue::Bullet {

    class BulletComponentImpl : public BulletComponent
    {
    private:
        btScalar fixedTimeStep = 1.0/60.0;
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
        BulletComponentImpl(BodyBuilder* bodyBuilder, ConstraintBuilder* constraintBuilder);

        ~BulletComponentImpl() override;

        void setDebugMode(bool debugMode) override;

        void addLink(Link *link) override;

        void setDebugDrawer(btIDebugDraw* drawer) override;

        void setOnTick(TickHandler aBlock) override;

        void setOnPreTick(TickHandler aBlock) override;

        void onPhysics(Scalar timeElapsed) override;

        void onGraphics(Scalar timeElapsed) override;

        void removeConstraint(ConstraintObj *constraint) override;

        ConstraintObj * addConstraint(ConstraintStyle const& style, BulletAttribute* attrA, BulletAttribute* attrB) override;

        BulletAttribute *addNode(Node *node) override;
    };
}
