#pragma once

#include <string>

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

namespace Glue { namespace Irrlicht {

class Component
{
private:
    std::string mediaPath;

    Event* events;
    EventDispatch* eventDispatch;
    Keyboard* keyboard;
    Mouse* mouse;
    GuiEvents* guiEvents;

    irr::IrrlichtDevice* device;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* smgr;
    irr::video::SExposedVideoData* videoData;
    Assets* assets;

    void* sound;
    irr::gui::IGUIEnvironment* gui;
    irr::scene::ISceneCollisionManager* collMan;
    irr::scene::IMeshManipulator* meshMan;

    SceneNodeBuilder* sceneNodeBuilder;

    // window title
    std::string title;

    irr::ITimer* deviceTimer;
    long frames;
    irr::video::SColor backColor;

    Camera* camera;

    Graph* graph;

public:

    Component();
    ~Component();

    Component& setGraph(Graph* value);

    void addNode(Node* node);
    void playSound(std::string const& file);
    void beforeGraphics();
    void onGraphics(Scalar timeElapsed);
    void afterGraphics();
    bool shouldRun() const;
    Node* nodeToGameObj(irr::scene::ISceneNode*);
    void removeObj(Node* obj);
};

}}
