#include "Glue/Model/Node.hpp"

#include "Glue/Utility/variant_helpers.hpp"

namespace Glue
{

    Node::Node(
        btRigidBody* rigidBody,
        irr::scene::ISceneNode* sceneNode,
        MotionStateAnimator* motionState) :
            rigidBody(rigidBody),
            sceneNode(sceneNode),
            motionState(motionState)
    {
    }

Node::~Node()
{
}

} // namespace Glue
