#include "Glue/Startup.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Irrlicht/Irrlicht.hpp"
#include "Glue/Bullet/Bullet.hpp"
#include "Glue/Avatar/Avatar.hpp"

#include <iostream>
#include <optional>

namespace Glue {

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

//time := RootModule Model Time clone
//graph addComponent(time)
//
//props := RootModule LevelSystem Props clone
//props setGraph(graph)
//
//writeln("Done adding components to engine.")
//
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
//)
//
//)
//
//if (loadError != nil,
//    writeln("error: ", loadError)
//    writeln("error caughtMessage: ", loadError caughtMessage)
//    if( loadError caughtMessage != nil,
//        writeln("line number: ", loadError caughtMessage lineNumber)
//    )
//    if( loadError originalCall != nil,
//        if( loadError originalCall target != nil,
//            writeln("original call target was ", loadError originalCall target)
//        )
//    )
//    loadError showStack
//    Exception raise("script loading may have failed")
//)
