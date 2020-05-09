#pragma once

#include "btRigidBody.h"
#include "ISceneNode.h"
#include "Glue/Animators/MotionStateAnimator.hpp"

namespace Glue
{
struct Node
{
    btRigidBody* rigidBody;
    irr::scene::ISceneNode* sceneNode;
    MotionStateAnimator* motionState;

    Node(
        btRigidBody* rigidBody,
        irr::scene::ISceneNode* sceneNode,
        MotionStateAnimator* motionState);

    ~Node();
};

}
