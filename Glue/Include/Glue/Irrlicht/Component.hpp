#pragma once

namespace irr { namespace video {
    class SColor;
    class IVideoDriver;
    class SExposedVideoData;
}}

namespace irr { namespace gui {
    class IGUIEnvironment;
}}

namespace irr { namespace scene {
    class ISceneManager;
    class ISceneCollisionManager;
    class IMeshManipulator;
}}

namespace irr {
    class IrrlichtDevice;
    class ITimer;
}

namespace Glue {

class Event;
class EventDispatch;
class Keyboard;
class Mouse;
class GuiEvents;
class Assets;
class SceneNodeBuilder;
class Camera;

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

}
