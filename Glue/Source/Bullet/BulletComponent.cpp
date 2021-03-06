#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include "Glue/Bullet/BulletComponent.hpp"
#include "Glue/Bullet/BulletAttribute.hpp"
#include "Glue/Bullet/BulletShape.hpp"

#include "Glue/Model/Link.hpp"
#include "Glue/Model/Shape.hpp"

#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"

using namespace Glue::Irrlicht;

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

    LinkAttribute* BulletComponent::addLink(Link* link)
    {
        return nullptr;

/*
        if (link->get_style().linkType == LinkTypes::physConstraint)
        {
            if (!link->get_style().constraint)
                throw std::logic_error("linkType is physConstraint but no constraint style is provided");

            auto attrA = find_attribute<IBulletAttribute>(link->get_fromNode());
            auto attrB = find_attribute<IBulletAttribute>(link->get_toNode());

            if (!attrA)
                throw std::logic_error("fromNode has no Bullet attribute.");

            if (!attrB)
                throw std::logic_error("toNode has no Bullet attribute");

            auto linkAttr = addConstraint(*(link->get_style().constraint), attrA, attrB);
            link->addAttribute(linkAttr);
            return linkAttr;
        }
        else
        {
            return nullptr;
        }
*/
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

    ShapeAttribute* BulletComponent::addShape(Shape* shape)
    {
        ShapeStyle node_style; // = shape->get_style();

        IIrrlichtShape* irr_shape; // = find_attribute<IIrrlichtShape>(shape);
        IMesh* mesh = irr_shape ? irr_shape->get_mesh() : nullptr;

        btCollisionShape* collision_shape = bodyBuilder->createShape(node_style, mesh);

        return new BulletShape(collision_shape);
    }

    NodeAttribute* BulletComponent::addNode(Node* node)
    {
        NodeStyle node_style; // = node->get_style();
        Shape* shape; // = node->get_shape();

        IBulletShape* bullet_shape; // = find_attribute<IBulletShape>(shape);
        btCollisionShape* collision_shape = bullet_shape->get_collision_shape();
        BodyConstructionInfo constrInfo = bodyBuilder->createConstructionInfo(node_style, collision_shape);

        btRigidBody* body = bodyBuilder->addToWorld(
                node_style,
                dynamicsWorld,
                constrInfo.body);

        IBulletAttribute* blt_attr = new BulletAttribute(
                node_style,
                body,
                constrInfo.motion_state,
                this);

        //node->addAttribute(blt_attr);

        return blt_attr;
    }
}
