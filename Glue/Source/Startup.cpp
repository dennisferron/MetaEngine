#include "Glue/Startup.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Irrlicht/Irrlicht.hpp"
#include "Glue/Bullet/Bullet.hpp"
#include "Glue/Avatar/Avatar.hpp"

#include <iostream>
#include <optional>

namespace Glue {

    void addPlayer()
    {
//addPlayer := method(
//    RootModule lexicalDo(
//        avatarCameraNode := graph addNode(Styles GameObjStyles EmptyStyle)
//        avatarCameraNode addAttribute(Avatar Camera clone)
//
//        playerNode := graph addNode(Avatar PlayerStyle)
//        avatarComp attachControl(playerNode)
//
//        graph addLink(Styles LinkStyles LookAtStyle, avatarCameraNode, playerNode)
//    )
    }


    void do_startup()
    {
        auto avatar_cmp = new Avatar::AvatarComponent();
        auto blt_cmp = new Bullet::BulletComponent();
        auto irr_cmp = new Irrlicht::IrrlichtComponent();

        irr::ITimer* device_timer = irr_cmp->get_deviceTimer();
        auto time_cmp = new TimeComponent(device_timer);

        auto graph = new Graph(avatar_cmp, blt_cmp, irr_cmp, time_cmp);

        //time_cmp->runLoop();
    }


}

