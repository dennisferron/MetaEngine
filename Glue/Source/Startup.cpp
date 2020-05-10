#include "Glue/Startup.hpp"
#include "Glue/Engine.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace Glue {

/*
    void addPlayer(Graph* graph, Glue::Avatar::AvatarComponent* avatarComp)
    {
        auto avatarCameraNode = graph->addNode(Glue::GameObjStyles::EmptyStyle());
        auto avatar_camera = new Glue::Avatar::Camera();
        // TODO:  Come up with different way to add camera than making it a node attribute.
        //avatarCameraNode->addAttribute(avatar_camera);

        auto playerNode = graph->addNode(Glue::Avatar::PlayerStyle());
        avatarComp->attachControl(playerNode);

        // TODO:
        graph->addLink( Glue::LinkStyles::LookAtStyle(), avatarCameraNode, playerNode);
    }
*/

    void do_startup()
    {
        IrrlichtDevice *device =
                createDevice(EDT_OPENGL, dimension2d<u32>(640, 480), 16,
                             false, false, false, 0);
        device->setWindowCaption(L"Engine Startup");

        Engine engine(device);

        ISceneManager* smgr = device->getSceneManager();
        smgr->addCameraSceneNode(0, vector3df(8,3,-10), vector3df(0,0,0));

        //Scene scene(smgr);

        engine.main_loop();

        int x = 0;
    }


}

