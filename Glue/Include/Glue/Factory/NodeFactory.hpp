#pragma once

#include "Glue/Model/Node.hpp"
#include "Glue/Model/Shape.hpp"
#include "Glue/Styles/NodeStyle.hpp"
#include "Glue/Animators/MotionStateAnimator.hpp"

namespace Glue
{
    class NodeFactory
    {
    private:
        btDynamicsWorld* dynamicsWorld;
        irr::scene::ISceneManager* smgr;

        btRigidBody::btRigidBodyConstructionInfo createConstructionInfo(
                NodeStyle const& style,
                btCollisionShape* physShape,
                btMotionState* motionState) const;

        btRigidBody* addToWorld(
                NodeStyle const& style,
                btRigidBody::btRigidBodyConstructionInfo const& rbInfo) const;

        irr::scene::ISceneNode* buildSceneNode(NodeStyle const& style, IMesh* mesh) const;

        irr::video::ITexture* loadTexture(GameObjStyle const& style, std::string const& key) const;

    public:
        NodeFactory(btDynamicsWorld* dynamicsWorld, irr::scene::ISceneManager* smgr);
        Node* create_node(NodeStyle const& style, Shape* shape);
    };
}
