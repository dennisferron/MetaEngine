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
        irr::IrrlichtDevice* device = nullptr;
        irr::video::IVideoDriver* driver = nullptr;
        irr::video::SExposedVideoData videoData;

        void* sound = nullptr;

        irr::ITimer* deviceTimer = nullptr;
        long frames;
        irr::video::SColor backColor;

        btIDebugDraw* debugDrawer;
    };

    class Scene
    {
    private:
        irr::scene::ISceneManager* smgr = nullptr;
        irr::scene::ISceneCollisionManager* collMan = nullptr;
        irr::scene::IMeshManipulator* meshMan = nullptr;

        ISceneNodeBuilder* sceneNodeBuilder = nullptr;

        Camera* camera = nullptr;

        IBodyBuilder* bodyBuilder = nullptr;
        IConstraintBuilder* constraintBuilder = nullptr;

    };

    class World
    {
    private:
        btDynamicsWorld* dynamicsWorld = nullptr;

        btScalar fixedTimeStep = 1.0 / 60.0;
        int subframes = 30;
        btCollisionConfiguration* collisionConfiguration = nullptr;
        btDispatcher* dispatcher = nullptr;  // This is a bullet physics thing, not associated with UI event dispatch
        btBroadphaseInterface* broadphaseInterface = nullptr;
        btConstraintSolver* solver = nullptr;
        btSoftBodyWorldInfo softBodyWorldInfo;
        Bullet::ScriptedWorldManager scriptWorldMgr;
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
