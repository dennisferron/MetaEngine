#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Model/ModelInterfaces.hpp"

class btRigidBody;

namespace irr::scene
{
    class ISceneNode;
}

namespace Glue
{
    class MotionStateAnimator;

class Node
{
private:

    btRigidBody* rigidBody;
    irr::scene::ISceneNode* sceneNode;
    MotionStateAnimator* motionState;

public:

    Node(
        btRigidBody* rigidBody,
        irr::scene::ISceneNode* sceneNode,
        MotionStateAnimator* motionState);

    ~Node();
};

}
