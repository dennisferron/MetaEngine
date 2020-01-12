#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include "Glue/Bullet/BulletComponentImpl.hpp"

namespace Glue::Bullet
{

    BulletComponentImpl::BulletComponentImpl(
            BodyBuilder* bodyBuilder,
            ConstraintBuilder* constraintBuilder)
        :
            bodyBuilder(bodyBuilder),
            constraintBuilder(constraintBuilder)
    {
        // Enable softbody collisions
        collisionConfiguration = new btSoftBodyRigidBodyCollisionConfiguration();

        ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
        dispatcher = new btCollisionDispatcher(collisionConfiguration);

        ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        broadphaseInterface = new btDbvtBroadphase();

        ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        solver = new btSequentialImpulseConstraintSolver();

        //setDynamicsWorld(btDiscreteDynamicsWorld new(dispatcher,broadphaseInterface,solver,collisionConfiguration))
        dynamicsWorld = new btSoftRigidDynamicsWorld(dispatcher, broadphaseInterface, solver, collisionConfiguration);

        // Gravity in approximate meters per second per second
        dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

        //setDebugMode(DBG_DrawConstraints)

        // Created with tmp so don't need to delete
        softBodyWorldInfo.m_dispatcher = dispatcher;
        softBodyWorldInfo.m_broadphase = broadphaseInterface;
        softBodyWorldInfo.m_sparsesdf.Initialize(2383);
        //softBodyWorldInfo.m_sparsesdf.Reset();  // Initialize resets
        softBodyWorldInfo.air_density = 1.2f;
        softBodyWorldInfo.water_density = 0;
        softBodyWorldInfo.water_offset = 0;
        softBodyWorldInfo.water_normal = btVector3(0,0,0);  // TODO: Should one of these be 1?
        softBodyWorldInfo.m_gravity = btVector3(0,-9.81,0);
        //softBodyWorldInfo.m_gravity = btVector3(0,0,0);
    }

    BulletComponentImpl::~BulletComponentImpl()
    {
        delete bodyBuilder;
        delete dynamicsWorld;
        delete solver;
        delete broadphaseInterface;
        delete dispatcher;
        delete collisionConfiguration;
    }

    void BulletComponentImpl::setDebugMode(bool debugMode)
    {
        dynamicsWorld->getDebugDrawer().setDebugMode(debugMode);
    }

    void BulletComponentImpl::addLink(Link *link)
    {
        if (link->style.linkType == LinkTypes::physConstraint)
        {
            if (!link->style.constraint)
                throw std::logic_error("linkType is physConstraint but no constraint style is provided");

            auto attrA = link->fromNode->get_bullet_attribute();
            auto attrB = link->toNode->get_bullet_attribute();

            if (!attrA)
                throw std::logic_error("fromNode has no Bullet attribute.");

            if (!attrB)
                throw std::logic_error("toNode has no Bullet attribute");

            auto linkAttr = addConstraint(*(link->style.constraint), attrA, attrB)
            link->addAttribute(linkAttr);
        }
    }

    void BulletComponentImpl::setDebugDrawer(btIDebugDraw *drawer)
    {
       dynamicsWorld->setDebugDrawer(debugDrawer);
    }

    void BulletComponentImpl::setOnTick(TickHandler aBlock)
    {
        scriptWorldMgr.setOnTick(*dynamicsWorld, aBlock);
    }

    void BulletComponentImpl::setOnPreTick(TickHandler aBlock)
    {
        scriptWorldMgr.setOnPreTick(*dynamicsWorld, aBlock);
    }

    void BulletComponentImpl::onPhysics(Scalar timeElapsed)
    {
        dynamicsWorld->stepSimulation(
                timeElapsed/1000.0,
                subframes,
                fixedTimeStep);
    }

    void BulletComponentImpl::onGraphics(Scalar timeElapsed)
    {
        // Enable this to see debug lines for all the physics objects.
        // If you suspect a physical object is out of sync with the graphical
        // object, you should enable this.
        dynamicsWorld->debugDrawWorld();
    }

    void BulletComponentImpl::removeConstraint(ConstraintObj* constraint)
    {
        if (!constraint)
            throw std::logic_error("ConstraintObj was null");

        dynamicsWorld->removeConstraint(constraint->constraint);

        if (constraint->attrA)
            constraint->attrA->removeConstraintsA(constraint);

        if (constraint->attrB)
            constraint->attrB->removeConstraintsB(constraint);

        constraint->attrA = nullptr;
        constraint->attrB = nullptr;
    }

    ConstraintObj* BulletComponentImpl::addConstraint(ConstraintStyle const& style, BulletAttribute* attrA, BulletAttribute* attrB)
    {
        if (!attrA && !attrB)
            throw std::logic_error("addConstraint attrA and attrB are both null");

        auto constraint = constraintBuilder->create(
                style,
                attrA->getRigidBody(),
                attrB->getRigidBody());

        if (constraint == nullptr)
            return nullptr;

        dynamicsWorld->addConstraint(
                constraint->constraint,
                style.disableLinkedBodyCollisions);

        if (attrA)
            attrA->addConstraintA(constraint);

        if (attrB)
            attrB->addConstraintB(constraint);

        return constraint
    }

    BulletAttribute* BulletComponentImpl::addNode(Node* node, IMesh* mesh)
    {
        btCollisionShape* shape = bodyBuilder->createShape(node->style, mesh);
        auto constrInfo = bodyBuilder->createConstructionInfo(node->style, shape);

         btRigidBody* body = bodyBuilder->addToWorld(
                 node->style,
                dynamicsWorld,
                constrInfo);

        // Note:  This should also be multiply inherited from an animator.
        // We might need to create an intermediate class instead of sideways cast.
        btMotionState* motionState = constrInfo.m_motionState;

        auto blt_attr = new BulletAttribute(
                node->style,
                body,
                motionState);

        node->addAttribute(blt_attr);

        return blt_attr;
    }
}
