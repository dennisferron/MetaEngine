#pragma once

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
                MotionState* motionState) const;

        btRigidBody* addToWorld(
                NodeStyle const& style,
                btRigidBody::btRigidBodyConstructionInfo const& rbInfo) const;

        ISceneNode* buildSceneNode(NodeStyle const& style) const;

    public:
        NodeFactory(btDynamicsWorld* dynamicsWorld, irr::scene::ISceneManager* smgr);
        Node* create_node(NodeStyle const& style, Shape* shape);
    };
}
