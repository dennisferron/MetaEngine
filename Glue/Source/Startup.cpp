#include "Glue/Startup.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Irrlicht/Irrlicht.hpp"
#include "Glue/Bullet/Bullet.hpp"
#include "Glue/Avatar/Avatar.hpp"

#include <iostream>
#include <optional>

namespace Glue {

    struct Startup::Impl
    {
        Graph graph;
        Avatar::AvatarComponent* avatarComp;
        Bullet::BulletComponent* bltComp;
        Irrlicht::IrrlichtComponent* irrComp;
    };

    Startup::Startup()
        : impl(new Startup::Impl())
    {
        std::cout << "Engine startup\n";
    }

    Startup::~Startup()
    {

    }

    void Startup::add_components()
    {
        impl->avatarComp = new Avatar::AvatarComponent();
        impl->bltComp = new Bullet::BulletComponent();
        impl->irrComp = new Irrlicht::IrrlichtComponent();
    }

}

//graph addComponent(
//    irrComp := RootModule Irrlicht Component clone
//)
//irrComp setGraph(graph)
//
//graph addComponent(
//    bltComp := RootModule Bullet Component clone
//)
//
//avatarComp := RootModule Avatar Component clone
//graph addComponent(
//    avatarComp
//)
//
//editorGUI := RootModule EditorGUI Component clone
//graph addComponent(
//    editorGUI
//    , RootModule Interactions Component LoadEditorGUI
//)
//
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
