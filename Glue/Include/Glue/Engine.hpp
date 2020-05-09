#pragma once

#include "Glue/Factory/ShapeFactory.hpp"
#include "Glue/Factory/NodeFactory.hpp"
#include "Glue/Factory/LinkFactory.hpp"

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

    class Engine
    {
    private:
        irr::IrrlichtDevice* device;

        btIDebugDraw* debugDrawer = nullptr;

        long frames = 0;
        //void* sound = nullptr;

        //Camera* camera;

        btScalar fixedTimeStep = 1.0 / 60.0;
        int subframes = 30;

        btDynamicsWorld* dynamicsWorld;

        btCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;  // This is a bullet physics thing, not associated with UI event dispatch
        btBroadphaseInterface* broadphaseInterface;
        btConstraintSolver* solver;
        btSoftBodyWorldInfo softBodyWorldInfo;
        Bullet::ScriptedWorldManager scriptWorldMgr;

        ShapeFactory* shape_factory;
        NodeFactory* node_factory;
        LinkFactory* link_factory;

    public:
        Engine(irr::IrrlichtDevice* device);
        ~Engine();
        void main_loop();
    };

}
