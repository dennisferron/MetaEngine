#include "Glue/Startup.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Irrlicht/Irrlicht.hpp"
#include "Glue/Bullet/BulletComponentImpl.hpp"
#include "Glue/Avatar/Avatar.hpp"
#include "Glue/Styles/GameObjStyles.hpp"
#include "Glue/Avatar/PlayerStyle.hpp"
#include "Glue/Styles/LinkStyles.hpp"

#include <iostream>
#include <optional>

namespace Glue {

    void addPlayer(Graph* graph, Glue::Avatar::AvatarComponent* avatarComp)
    {
        auto avatarCameraNode = graph->addNode(Glue::GameObjStyles::EmptyStyle());
        auto avatar_camera = new Glue::Avatar::Camera();
        avatarCameraNode->addAttribute(avatar_camera);

        auto playerNode = graph->addNode(Glue::Avatar::PlayerStyle());
        avatarComp->attachControl(playerNode);

        // TODO:
        graph->addLink( Glue::LinkStyles::LookAtStyle(), avatarCameraNode, playerNode);
    }

    void do_startup()
    {
        auto avatar_cmp = new Avatar::AvatarComponent();
        auto bodyBuilder = new Bullet::BodyBuilder();
        auto blt_cmp = new Bullet::BulletComponentImpl(bodyBuilder);
        auto irr_cmp = new Irrlicht::IrrlichtComponent();

        irr::ITimer* device_timer = irr_cmp->get_deviceTimer();
        auto time_cmp = new TimeComponent(device_timer);

        auto graph = new Graph(avatar_cmp, blt_cmp, irr_cmp, time_cmp);

        addPlayer(graph, avatar_cmp);

        //time_cmp->runLoop();
    }


}

