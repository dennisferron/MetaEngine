#include "Glue/Startup.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Model/TimeComponent.hpp"
#include "Glue/Bullet/BulletComponent.hpp"
#include "Glue/Styles/GameObjStyles.hpp"
#include "Glue/Avatar/PlayerStyle.hpp"
#include "Glue/Styles/LinkStyles.hpp"
#include "Glue/Avatar/AvatarComponent.hpp"
#include "Glue/Avatar/Camera.hpp"

#include <iostream>
#include <optional>
#include <Glue/Bullet/BodyBuilder.hpp>
#include <Glue/Bullet/ConstraintBuilder.hpp>
#include <Glue/Irrlicht/IrrlichtComponent.hpp>

namespace Glue {

    void addPlayer(Graph* graph, Glue::Avatar::AvatarComponent* avatarComp)
    {
/*
        auto avatarCameraNode = graph->addNode(Glue::GameObjStyles::EmptyStyle());
        auto avatar_camera = new Glue::Avatar::Camera();
        // TODO:  Come up with different way to add camera than making it a node attribute.
        //avatarCameraNode->addAttribute(avatar_camera);

        auto playerNode = graph->addNode(Glue::Avatar::PlayerStyle());
        avatarComp->attachControl(playerNode);

        // TODO:
        graph->addLink( Glue::LinkStyles::LookAtStyle(), avatarCameraNode, playerNode);
*/
    }

    void do_startup()
    {
/*
        auto avatar_cmp = new Avatar::AvatarComponent();
        auto bodyBuilder = new Bullet::BodyBuilder();
        auto constrBuilder = new Bullet::ConstraintBuilder();
        auto blt_cmp = new Bullet::BulletComponent(bodyBuilder, constrBuilder);
        auto irr_cmp = new Irrlicht::IrrlichtComponent();

        irr::ITimer* device_timer = irr_cmp->get_deviceTimer();
        auto time_cmp = new TimeComponent(device_timer);

        auto graph = new Graph(avatar_cmp, blt_cmp, irr_cmp, time_cmp);

        addPlayer(graph, avatar_cmp);

        //time_cmp->runLoop();
*/
    }


}

