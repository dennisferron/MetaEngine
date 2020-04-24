#pragma once

#include "Glue/Bullet/ScriptedWorldManager.hpp"

#include "btScalar.h"
#include "BulletSoftBody/btSoftBody.h"

#include "SExposedVideoData.h"
#include "SColor.h"

namespace irr
{
    class IrrlichtDevice;
    class ITimer;

    namespace video
    {
        class IVideoDriver;
    }

    namespace scene
    {
        class ISceneManager;
        class ISceneCollisionManager;
        class IMeshManipulator;
    }

    namespace gui
    {
        class IGUIEnvironment;
    }
}

class btIDebugDraw;
class btDynamicsWorld;
class btCollisionConfiguration;
class btDispatcher;
class btBroadphaseInterface;
class btConstraintSolver;

namespace Glue
{
    class ISceneNodeBuilder;
    class Camera;
    class IBodyBuilder;
    class IConstraintBuilder;
    class Assets;
    class Event;
    class EventDispatch;
    class Keyboard;
    class Mouse;
    class GuiEvents;

    class Engine
    {
    private:
        irr::IrrlichtDevice* device;
        irr::video::IVideoDriver* driver;
        irr::ITimer* deviceTimer;

        btIDebugDraw* debugDrawer = nullptr;

        long frames = 0;
        void* sound = nullptr;

    public:
        Engine(irr::IrrlichtDevice* device);
        void main_loop();
    };

    class Scene
    {
    private:
        irr::scene::ISceneManager* smgr;
        irr::scene::ISceneCollisionManager* collMan;
        irr::scene::IMeshManipulator* meshMan;

        ISceneNodeBuilder* sceneNodeBuilder;

        Camera* camera;

        IBodyBuilder* bodyBuilder;
        IConstraintBuilder* constraintBuilder;

    public:
        Scene(irr::scene::ISceneManager* smgr,
                ISceneNodeBuilder* sceneNodeBuilder,
                Camera* camera,
                IBodyBuilder* bodyBuilder,
                IConstraintBuilder* constraintBuilder);
    };

    class World
    {
    private:
        btScalar fixedTimeStep = 1.0 / 60.0;
        int subframes = 30;

        btDynamicsWorld* dynamicsWorld = nullptr;

        btCollisionConfiguration* collisionConfiguration = nullptr;
        btCollisionDispatcher* dispatcher = nullptr;  // This is a bullet physics thing, not associated with UI event dispatch
        btBroadphaseInterface* broadphaseInterface = nullptr;
        btConstraintSolver* solver = nullptr;
        btSoftBodyWorldInfo softBodyWorldInfo;
        Bullet::ScriptedWorldManager scriptWorldMgr;

    public:
        World();
        ~World();
    };

    class UserInterface
    {
    private:
        // window title
        std::wstring title;

        std::string mediaPath;
        Assets* assets = nullptr;

        Event* events = nullptr;
        EventDispatch* eventDispatch = nullptr;
        Keyboard* keyboard = nullptr;
        Mouse* mouse = nullptr;
        GuiEvents* guiEvents = nullptr;

        irr::gui::IGUIEnvironment* gui = nullptr;
    };

}
