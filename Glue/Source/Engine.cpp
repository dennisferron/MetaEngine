#include "Glue/Engine.hpp"

#include "irrlicht.h"

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"

#include <iostream>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::io;
using namespace irr::gui;

namespace Glue
{
    Engine::Engine(
        irr::IrrlichtDevice* device) :
            device(device)
    {
        broadphaseInterface = new btDbvtBroadphase();
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
        solver = new btSequentialImpulseConstraintSolver;
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphaseInterface, solver, collisionConfiguration);
        dynamicsWorld->setGravity(btVector3(0, -10, 0));

        ISceneManager* smgr = device->getSceneManager();
        shape_factory = new ShapeFactory(smgr->getGeometryCreator());
        node_factory = new NodeFactory(dynamicsWorld, smgr);
        link_factory = new LinkFactory();
    }

    void Engine::main_loop()
    {
        int num_frames = 0;

        ShapeStyle box_shape_style;
        box_shape_style.setShape(ObjShapes::coneX);
        Shape* box_shape = shape_factory->createShape(box_shape_style);

        NodeStyle box_node_style;
        Node* box_node = node_factory->create_node(box_node_style, box_shape);

        ISceneManager* smgr = device->getSceneManager();
        IGUIEnvironment* guienv = device->getGUIEnvironment();
        IVideoDriver* driver = device->getVideoDriver();
        irr::ITimer* deviceTimer = device->getTimer();

        u32 lastTime = deviceTimer->getTime();
        u32 currentTime = deviceTimer->getTime();

        Scalar fixedTimeStep = 1.0/60.0;
        int maxSubframes = 30;

        while(device->run())
        {
            lastTime = currentTime;
            currentTime = deviceTimer->getTime();
            Scalar timeStep = (currentTime - lastTime) / 1000.0;

            ++num_frames;

            u16 clearFlag=(u16)(ECBF_COLOR|ECBF_DEPTH);
            SColor clearColor = SColor(0,200,200,200);
            f32 clearDepth = 1.f;
            u8 clearStencil = 0;
            const SExposedVideoData& videoData=SExposedVideoData();
            core::rect<s32>* sourceRect = 0;

            driver->beginScene(clearFlag, clearColor, clearDepth, clearStencil, videoData, sourceRect);

            dynamicsWorld->stepSimulation(timeStep, maxSubframes, fixedTimeStep);

            if ((num_frames <= 240) && (num_frames % 60 == 0))
            {
                btTransform trans;
                box_node->motionState->getWorldTransform(trans);
                std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
            }

            smgr->drawAll();
            guienv->drawAll();

            driver->endScene();

            if (num_frames > 20000)
                break;
        }
    }

    Engine::~Engine()
    {
        device->drop();
        delete dynamicsWorld;
        delete solver;
        delete dispatcher;
        delete collisionConfiguration;
        delete broadphaseInterface;
    }
}