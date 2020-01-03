#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include "Glue/Bullet/BulletComponentImpl.hpp"

namespace Glue::Bullet
{

    BulletComponentImpl::BulletComponentImpl(BodyBuilder* bodyBuilder) :
            bodyBuilder(bodyBuilder),
            scriptWorldMgr(),
            softBodyWorldInfo()
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
    {}

    void BulletComponentImpl::addLink(Link *link)
    {}

    void BulletComponentImpl::setDebugDrawer(btIDebugDraw *drawer)
    {}

    void BulletComponentImpl::setOnTick(TickHandler aBlock)
    {}

    void BulletComponentImpl::setOnPreTick(TickHandler aBlock)
    {}

    void BulletComponentImpl::onPhysics(Scalar timeElapsed)
    {}

    void BulletComponentImpl::onGraphics(Scalar timeElapsed)
    {}

    void BulletComponentImpl::removeConstraint(ConstraintObj *constraint)
    {}

    ConstraintObj *BulletComponentImpl::addConstraint(LinkStyle *style, btRigidBody &attrA, btRigidBody &attrB)
    { throw "Not implemented."; }

    BulletAttribute *BulletComponentImpl::addNode(Node *node)
    { throw "Not implemented."; }

}

/*

        setDebugMode := method(debugMode,
            dynamicsWorld getDebugDrawer setDebugMode(debugMode)
        )

        addLink := method(link,
            if( link style jointType != "none" and module ConstraintBuilder hasSlot(link style jointType),
                attrA := link fromNode ?findAttribute(BulletAttribute)
                attrB := link toNode ?findAttribute(BulletAttribute)

                if( attrA == nil and attrB == nil,
                    writeln("Link style " .. (
                        link style jointType) .. (
                        " is supported by constraint builder, but both the from node (" ) .. (
                        if(link fromNode == nil, "nil", link fromNode style)) .. (
                        ") and the to node (") .. (
                        if(link toNode == nil, "nil", link toNode style)) .. (
                        ") do not have Bullet attributes attached.")
                    )
                ,
                    linkAttr := addConstraint(link style, attrA, attrB)
                    link addAttribute(linkAttr)
                )
            )
        )
    )

    Component setDebugDrawer := method(drawer,
        dynamicsWorld setDebugDrawer(debugDrawer)
    )

    Component setOnTick := method(aBlock,
        scriptWorldMgr setOnTick(dynamicsWorld, block(worldptr, timeStep, aBlock call(timeStep)))
    )

    Component setOnPreTick := method(aBlock,
        scriptWorldMgr setOnPreTick(dynamicsWorld, block(worldptr, timeStep, aBlock call(timeStep)))
    )

    Component onPhysics := method(timeElapsed,
        dynamicsWorld stepSimulation(timeElapsed/1000.0, subframes, fixedTimeStep)
    )

    Component onGraphics := method(timeElapsed,
        // Enable this to see debug lines for all the physics objects.
        // If you suspect a physical object is out of sync with the graphical
        // object, you should enable this.
        //dynamicsWorld debugDrawWorld()
        nil
    )

    Component removeConstraint := method(constraint,
        if( constraint != nil,

            dynamicsWorld removeConstraint(constraint constraint)

            if(constraint attrA != nil, constraint attrA constraintsA remove(constraint))
            if(constraint attrB != nil, constraint attrB constraintsB remove(constraint))

            constraint attrA = nil
            constraint attrB = nil
        )
    )

    Component addConstraint := method(style, attrA, attrB,

        if (attrA == nil and attrB == nil, Exception raise("addConstraint attrA and attrB are both nil; style is " .. style asString))

        constraint := module ConstraintBuilder create(style, attrA, attrB)

        if (constraint == nil,
            return nil
        ,
            dynamicsWorld addConstraint(constraint constraint, style disableLinkedBodyCollisions)

            if(attrA != nil, attrA constraintsA append(constraint))
            if(attrB != nil, attrB constraintsB append(constraint))

            return constraint
        )
    )

    Component addNode := method(node,
        style := node style
        result := bodyBuilder buildBody(style)
        if( result != nil,
            body := result body
            motionState := result anim
            node addAttribute(
                BulletAttribute clone setStyle(style) setRigidBody(body) setMotionState(motionState)
            )
        )
    )

    return Component
)
*/