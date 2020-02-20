#include "Glue/Irrlicht/IrrlichtComponent.hpp"

#include "SColor.h"
#include "IVideoDriver.h"
#include "SExposedVideoData.h"
#include "IGUIEnvironment.h"
#include "ISceneManager.h"
#include "ISceneCollisionManager.h"
#include "IMeshManipulator.h"
#include "IrrlichtDevice.h"
#include "ITimer.h"

#include "Glue/Irrlicht/UserInterface/EventDispatch.hpp"
#include "Glue/Irrlicht/UserInterface/GuiEvents.hpp"
#include "Glue/Irrlicht/UserInterface/Keyboard.hpp"
#include "Glue/Irrlicht/UserInterface/Menu.hpp"
#include "Glue/Irrlicht/UserInterface/Mouse.hpp"
#include "Glue/Irrlicht/UserInterface/MouseDragLinkAttribute.hpp"
#include "Glue/Irrlicht/UserInterface/SceneNodeSelector.hpp"

#include "Glue/Irrlicht/Assets.hpp"
#include "Glue/Irrlicht/Camera.hpp"
#include "Glue/Irrlicht/SceneNodeBuilder.hpp"

using namespace irr;
using namespace irr::core;
using namespace irr::video;

namespace Glue::Irrlicht
{
    IrrlichtComponent::IrrlichtComponent()
    {
        // TODO:  Connect with event dispatch from UserInterface component.

//            setEventDispatch(UserInterface EventDispatch clone)
//            setEvents(eventDispatch eventReceiver)

        // TODO:  Configure GuiEvents
//            setGuiEvents(UserInterface GuiEvents clone)
//            eventDispatch addHandler(EET_GUI_EVENT,
//                block(event,
//                    guiEvents handle(event)
//                )
//            )

        u32 MainWindow_sizeX = 800;
        u32 MainWindow_sizeY = 600;
        auto windowSize = dimension2du(MainWindow_sizeX, MainWindow_sizeY);
        auto deviceType = EDT_OPENGL; // or EDT_BURNINGSVIDEO, EDT_SOFTWARE, EDT_NULL
        impl->device = createDevice(deviceType, windowSize, 16, false, false, false, nullptr /* events */);

        if (!impl->device)
            throw std::runtime_error("Failed to create irrlicht device");

        impl->deviceTimer = impl->device->getTimer();
        impl->driver = impl->device->getVideoDriver();

        //            setAssets(module Assets clone setAssetPath(mediaPath) setDriver(driver))

        impl->smgr = impl->device->getSceneManager();

        impl->camera = new Camera(impl->smgr, impl->driver);
        impl->camera->createNode();

        //            shapeBuilder := module ShapeBuilder clone setDisplayShapes(
//                module DisplayShapes clone setGeometry(
//                    smgr getGeometryCreator
//                )
//            )
//
//            sceneNodes := module SceneNodes clone setSmgr(smgr)
//            setSceneNodeBuilder(
//                module SceneNodeBuilder clone setAssets(assets) setShapeBuilder(shapeBuilder) setSceneNodes(
//                    sceneNodes setAssets(assets)
//                )
//            )

//            //if( CppFunc hasSlot("createIrrKlangDevice"),
//            //	setSound(CppFunc createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_DEFAULT_OPTIONS, nil, IRR_KLANG_VERSION))
//            //)

        impl->smgr->addLightSceneNode(
                nullptr, // parent
                vector3df(0, 500, -50), // position
                SColorf(1, 1, 1, 1), // color
                200, // radius
                0 // id
        );

        impl->smgr->setAmbientLight(SColorf(0.2, 0.2, 0.2, 0.2));

        impl->gui = impl->device->getGUIEnvironment();

        impl->collMan = impl->smgr->getSceneCollisionManager();
        impl->meshMan = impl->smgr->getMeshManipulator();

        impl->title = impl->driver->getName();

//            setKeyboard(module UserInterface Keyboard clone)
//            eventDispatch addHandler(EET_KEY_INPUT_EVENT,
//                block(event,
//                    keyboard handle(event)
//                )
//            )
//
//            setMouse(module UserInterface Mouse clone)
//            mouse setGui(gui)
//            mouse setCollMan(collMan)
//            mouse setDriver(driver)
//            mouse setIrrComp(self)
//            eventDispatch addHandler(EET_MOUSE_INPUT_EVENT,
//                block(event,
//                    mouse handle(event)
//                )
//            )
    }

    IrrlichtComponent::~IrrlichtComponent()
    {
        impl->device->drop();
    }

    irr::ITimer* IrrlichtComponent::get_deviceTimer()
    {
        return impl->deviceTimer;
    }

    IrrlichtAttribute* IrrlichtComponent::addNode(Glue::Node* node)
    {
        auto sceneNode = impl->sceneNodeBuilder->buildSceneNode(node->style);

        if (sceneNode)
        {
            auto nodeAttr = new IrrlichtAttribute(node->style, sceneNode);
            node->addAttribute(nodeAttr);
            return nodeAttr;
        } else
        {
            return nullptr;
        }
    }

    void IrrlichtComponent::setGraph(Graph* graph)
    {
        impl->graph = graph;

        //if (impl->mouse)
        //    impl->mouse->setGraph(graph);
    }

    void IrrlichtComponent::playSound(std::string const& file)
    {
        // TODO:  Sound
//            if(sound != nil,
//                sound play2D(file, false, false, false, ESM_AUTO_DETECT, false)
//            )
    }

    void IrrlichtComponent::beforeGraphics()
    {
//
//        beforeGraphics := method(
//            driver beginScene(true, true, backColor, videoData, nil)
//        )
    }

    void IrrlichtComponent::onGraphics(Scalar timeElapsed)
    {
//        onGraphics := method(timeElapsed,
//
//            // Keep the camera in sync with the player position
//            //camera update
//
//            // Draws debug lines to show where the windowbox of the camera is.
//            //camera drawBox
//
//            // !!! Graphics happens here !!!
//            smgr drawAll
//
//            // !!! Menu UI happens here !!!
//            //if (menu != nil, menu draw)
//
//            // !!! If you don't draw the environment at the end none of your GUI elements show up! !!!
//            gui drawAll
//        )
    }

    void IrrlichtComponent::afterGraphics()
    {
//        afterGraphics := method(
//            driver endScene
//
//            frames = frames + 1
//            if (frames % 10 == 0,
//                device setWindowCaption(title .. (driver getFPS asString))
//            )
//        )
    }

    bool IrrlichtComponent::shouldRun() const
    {
        return impl->device->run();
    }

    Node* IrrlichtComponent::nodeToGameObj(irr::scene::ISceneNode*)
    {
        throw std::logic_error("Not implemented: nodeToGameObj");
//            anim := ScriptObjAnimator findIn(node)
//            if(anim == nil,
//                nil
//            ,
//                anim getScriptObj
//            )
    }

    void IrrlichtComponent::removeObj(Node* obj)
    {
        throw std::logic_error("TODO: decide whether to use IrrlichtAttribute destructor only for this");
    }
}
