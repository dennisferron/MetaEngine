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

    IGraph* graph = nullptr;

public:

    IrrlichtComponent(IGraph* graph);
    ~IrrlichtComponent();

    irr::ITimer* get_deviceTimer() final;

    IrrlichtAttribute* addNode(INode* node) final;
    void playSound(std::string const& file) final;
    void beforeGraphics() final;
    void onGraphics(Scalar timeElapsed) final;
    void afterGraphics() final;
    bool shouldRun() const final;
    INode* nodeToGameObj(irr::scene::ISceneNode*) final;
    void removeObj(INode* obj) final;
};

}
