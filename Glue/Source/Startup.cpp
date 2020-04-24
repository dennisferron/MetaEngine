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

        Assets* assets = nullptr;
        ISceneManager* smgr = device->getSceneManager();
        ShapeBuilder* shapeBuilder = new ShapeBuilder(smgr->getGeometryCreator());
        ISceneNodeBuilder* sceneNodeBuilder = new SceneNodeBuilder(shapeBuilder, assets, smgr);
        Camera* camera = nullptr;
        IBodyBuilder* bodyBuilder = nullptr;
        IConstraintBuilder* constraintBuilder = nullptr;

        //IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
        //IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

        IMesh* mesh = shapeBuilder->createShape();

        if (!node)
            throw std::runtime_error("Failed to load scene node");

        node->setMaterialFlag(EMF_LIGHTING, false);
        //node->setFrameLoop(0, 310);
        auto driver = device->getVideoDriver();
        node->setMaterialTexture( 0, driver->getTexture("media/sydney.bmp") );

        smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

        Scene scene(
            smgr,
            sceneNodeBuilder,
            camera,
            bodyBuilder,
            constraintBuilder);

        engine.main_loop();

        int x = 0;
    }


}

