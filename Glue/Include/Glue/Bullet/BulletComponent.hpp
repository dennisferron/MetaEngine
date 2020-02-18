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


namespace Glue::Bullet {

    class BulletComponent : public IBulletComponent
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
        BulletComponent(BodyBuilder* bodyBuilder, ConstraintBuilder* constraintBuilder);

        ~BulletComponent() override;

        void setDebugMode(bool debugMode) override;

        void addLink(Link *link) override;

        void setDebugDrawer(btIDebugDraw* drawer) override;

        void setOnTick(TickHandler aBlock) override;

        void setOnPreTick(TickHandler aBlock) override;

        void onPhysics(Scalar timeElapsed) override;

        void onGraphics(Scalar timeElapsed) override;

        void removeConstraint(IConstraintObj *constraint) override;

        IConstraintObj * addConstraint(ConstraintStyle const& style, BulletAttribute* attrA, BulletAttribute* attrB) override;

        IBulletAttribute *addNode(INode *node) override;
    };
}
