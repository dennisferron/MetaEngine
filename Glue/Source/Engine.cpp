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
            device(device),
            driver(device->getVideoDriver()),
            deviceTimer(device->getTimer())
    {
    }

    void Engine::main_loop()
    {
        int num_frames = 0;

        ISceneManager* smgr = device->getSceneManager();
        IGUIEnvironment* guienv = device->getGUIEnvironment();

        /*
        Ok, now we have set up the scene, lets draw everything:
        We run the device in a while() loop, until the device does not
        want to run any more. This would be when the user closed the window
        or pressed ALT+F4 in windows.
        */
        while(device->run())
        {
            ++num_frames;

            /*
            Anything can be drawn between a beginScene() and an endScene()
            call. The beginScene clears the screen with a color and also the
            depth buffer if wanted. Then we let the Scene Manager and the
            GUI Environment draw their content. With the endScene() call
            everything is presented on the screen.
            */

            u16 clearFlag=(u16)(ECBF_COLOR|ECBF_DEPTH);
            SColor clearColor = SColor(0,200,200,200);
            f32 clearDepth = 1.f;
            u8 clearStencil = 0;
            const SExposedVideoData& videoData=SExposedVideoData();
            core::rect<s32>* sourceRect = 0;

            driver->beginScene(clearFlag, clearColor, clearDepth, clearStencil, videoData, sourceRect);

            //dynamicsWorld->stepSimulation(1 / 60.f, 10);

            if ((num_frames <= 240) && (num_frames % 60 == 0))
            {
                btTransform trans;
                //fallRigidBody->getMotionState()->getWorldTransform(trans);
                std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
            }

            smgr->drawAll();
            guienv->drawAll();

            driver->endScene();

            if (num_frames > 1000)
                break;
        }
    }

    Scene::Scene(
        irr::scene::ISceneManager* smgr,
        ISceneNodeBuilder* sceneNodeBuilder,
        Camera* camera,
        IBodyBuilder* bodyBuilder,
        IConstraintBuilder* constraintBuilder) :
    smgr(smgr),
    collMan(smgr->getSceneCollisionManager()),
    meshMan(smgr->getMeshManipulator()),
    sceneNodeBuilder(sceneNodeBuilder),
    camera(camera),
    bodyBuilder(bodyBuilder),
    constraintBuilder(constraintBuilder)
    {}

    World::World()
    {
        broadphaseInterface = new btDbvtBroadphase();
        collisionConfiguration = new btDefaultCollisionConfiguration();
        dispatcher = new btCollisionDispatcher(collisionConfiguration);
        btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
        solver = new btSequentialImpulseConstraintSolver;
        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphaseInterface, solver, collisionConfiguration);
        dynamicsWorld->setGravity(btVector3(0, -10, 0));
    }

    World::~World()
    {
        delete dynamicsWorld;
        delete solver;
        delete dispatcher;
        delete collisionConfiguration;
        delete broadphaseInterface;
    }
}