#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include "Glue/Bullet/BulletComponent.hpp"
#include "Glue/Bullet/BulletAttribute.hpp"
#include "Glue/Bullet/BulletShape.hpp"

#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"

namespace Glue::Bullet
{

    BulletComponent::BulletComponent(
            IBodyBuilder* bodyBuilder,
            IConstraintBuilder* constraintBuilder)
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

    BulletComponent::~BulletComponent()
    {
        delete bodyBuilder;
        delete dynamicsWorld;
        delete solver;
        delete broadphaseInterface;
        delete dispatcher;
        delete collisionConfiguration;
    }

    void BulletComponent::setDebugMode(bool debugMode)
    {
        dynamicsWorld->getDebugDrawer()->setDebugMode(debugMode);
    }

    void BulletComponent::addLink(ILink *link)
    {
        if (link->get_style().linkType == LinkTypes::physConstraint)
        {
            if (!link->get_style().constraint)
                throw std::logic_error("linkType is physConstraint but no constraint style is provided");

            auto attrA = link->get_fromNode()->get_bullet_attribute();
            auto attrB = link->get_toNode()->get_bullet_attribute();

            if (!attrA)
                throw std::logic_error("fromNode has no Bullet attribute.");

            if (!attrB)
                throw std::logic_error("toNode has no Bullet attribute");

            auto linkAttr = addConstraint(*(link->get_style().constraint), attrA, attrB);
            link->addAttribute(linkAttr);
        }
    }

    void BulletComponent::setDebugDrawer(btIDebugDraw *drawer)
    {
       dynamicsWorld->setDebugDrawer(debugDrawer);
    }

    void BulletComponent::setOnTick(TickHandler aBlock)
    {
        scriptWorldMgr.setOnTick(*dynamicsWorld, aBlock);
    }

    void BulletComponent::setOnPreTick(TickHandler aBlock)
    {
        scriptWorldMgr.setOnPreTick(*dynamicsWorld, aBlock);
    }

    void BulletComponent::onPhysics(Scalar timeElapsed)
    {
        dynamicsWorld->stepSimulation(
                timeElapsed/1000.0,
                subframes,
                fixedTimeStep);
    }

    void BulletComponent::onGraphics(Scalar timeElapsed)
    {
        // Enable this to see debug lines for all the physics objects.
        // If you suspect a physical object is out of sync with the graphical
        // object, you should enable this.
        dynamicsWorld->debugDrawWorld();
    }

    void BulletComponent::removeConstraint(IConstraintObj* constraint)
    {
/*
        if (!constraint)
            throw std::logic_error("ConstraintObj was null");

        dynamicsWorld->removeConstraint(constraint->get_constraint());

        if (constraint->get_attrA())
            constraint->get_attrA()->removeConstraintsA(constraint);

        if (constraint->get_attrB())
            constraint->get_attrB()->removeConstraintsB(constraint);

        constraint->attrA = nullptr;
        constraint->attrB = nullptr;
*/
    }

    IConstraintObj* BulletComponent::addConstraint(ConstraintStyle const& style, IBulletAttribute* attrA, IBulletAttribute* attrB)
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
                constraint->get_constraint(),
                style.disableLinkedBodyCollisions);

        if (attrA)
            attrA->addConstraintA(constraint);

        if (attrB)
            attrB->addConstraintB(constraint);

        return constraint;
    }

    IBulletShape* BulletComponent::addShape(IShape* shape)
    {
        ShapeStyle const& node_style = shape->get_style();

        Irrlicht::IIrrlichtShape* irr_shape = shape->get_irrlicht_shape();
        IMesh* mesh = irr_shape ? irr_shape->get_mesh() : nullptr;

        btCollisionShape* collision_shape = bodyBuilder->createShape(node_style, mesh);

        return new BulletShape(collision_shape);
    }

    IBulletAttribute* BulletComponent::addNode(INode* node)
    {
        NodeStyle const& node_style = node->get_style();
        IShape* shape = node->get_shape();

        IBulletShape* bullet_shape = shape->get_bullet_shape();
        btCollisionShape* collision_shape = bullet_shape->get_collision_shape();
        BodyConstructionInfo constrInfo = bodyBuilder->createConstructionInfo(node_style, collision_shape);

        std::unique_ptr<btRigidBody> body = bodyBuilder->addToWorld(
                node_style,
                dynamicsWorld,
                constrInfo.body);

        IBulletAttribute* blt_attr = new BulletAttribute(
                node->get_style(),
                std::move(body),
                constrInfo.motion_state,
                this);

        node->addAttribute(blt_attr);

        return blt_attr;
    }
}
