#pragma once

#include "Glue/Model/Node.hpp"

#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"

#include "ITimer.h"
#include "ISceneNode.h"

#include <memory>
#include <string>

namespace Glue::Irrlicht
{

class IrrlichtComponent : public IIrrlichtComponent
{
private:
    std::string mediaPath;

    Event* events = nullptr;
    EventDispatch* eventDispatch = nullptr;
    Keyboard* keyboard = nullptr;
    Mouse* mouse = nullptr;
    GuiEvents* guiEvents = nullptr;

    irr::IrrlichtDevice* device = nullptr;
    irr::video::IVideoDriver* driver = nullptr;
    irr::scene::ISceneManager* smgr = nullptr;
    irr::video::SExposedVideoData videoData;
    Assets* assets = nullptr;

    void* sound = nullptr;
    irr::gui::IGUIEnvironment* gui = nullptr;
    irr::scene::ISceneCollisionManager* collMan = nullptr;
    irr::scene::IMeshManipulator* meshMan = nullptr;

    SceneNodeBuilder* sceneNodeBuilder = nullptr;

    // window title
    std::wstring title;

    irr::ITimer* deviceTimer = nullptr;
    long frames;
    irr::video::SColor backColor;

    Camera* camera = nullptr;

    Graph* graph = nullptr;

public:

    IrrlichtComponent();
    ~IrrlichtComponent();

    irr::ITimer* get_deviceTimer();

    IrrlichtAttribute* addNode(Glue::Node* node);
    void playSound(std::string const& file);
    void beforeGraphics();
    void onGraphics(Scalar timeElapsed);
    void afterGraphics();
    bool shouldRun() const;
    Node* nodeToGameObj(irr::scene::ISceneNode*);
    void removeObj(Node* obj);
    void setGraph(Graph* graph);
};

}
