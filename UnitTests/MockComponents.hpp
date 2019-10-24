#pragma once

class IIrrNodeAttribute
{
};

class IIrrComponent
{

};

struct NodeStyle
{
};

struct BallStyle
{
    double radius;
};

struct BoxStyle
{
    double xs;
    double ys;
    double zs;
};

class NodeInteraction
{
private:
public:
    virtual ~NodeInteraction() = 0;
};

NodeInteraction::~NodeInteraction() {}

class Node
{
private:
    std::unique_ptr<NodeStyle> style;
    std::map< Identity , std::unique_ptr<NodeInteraction const> > interactions;

public:

    template <typename T>
    Node(T const& style) : comp(this), std::make_unique<T>(style)
    {
    }

    void add_attribute(NodeAttribute* attr, PossibleInteractions*);
    //void add_interaction(NodeInteraction const* interaction);
};

// When all of the preconditions are met, create a T.
// Instead of returning the object, the PossibleInteraction
// should be allowed to manage in a different way.
template <typename T>
class PossibleInteraction
{
    //std::unique_ptr<T> create(Args...&& args) const;
};

class NodeList
{
private:
    std::vector<
    std::unique_ptr<
            PossibleInteraction<NodeInteraction>
    >
    > possible_interactions;

    std::vector<Node> nodes;
};

class Component
{
public:
    virtual void add_node(Node const& node) = 0;
};

class Animator
{
};

class SceneNode
{
public:
    void add_animator(Animator* anim)
    {
        std::cout << "add_animator\n";
    }

    void remove_animator(Animator* anim)
    {
        std::cout << "remove_animator\n";
    }
};

class IrrComp : public Component
{
private:
    std::vector< std::shared_ptr<SceneNode> > scene_nodes;
};

class MotionState
{
};

class RigidBody
{
public:
    void set_motion_state(MotionState* motion_state)
    {
        std::cout << "set_motion_state\n";
    }

    void unset_motion_state(MotionState* motion_state)
    {
        std::cout << "unset_motion_state\n";
    }
};

class PhysComp : public Component
{
private:
    std::vector< RigidBody > bodies;
};

class MotionStateAnimator : public MotionState, public Animator
{
};

class AddMotionStateAnimator : public NodeInteraction
{
private:
    SceneNode* node;
    RigidBody* body;
    MotionStateAnimator motion_anim;

public:
    AddMotionStateAnimator(SceneNode* node, RigidBody* body)
            : node(node), body(body), motion_anim()
    {
        node->add_animator(&motion_anim);
        body->set_motion_state(&motion_anim);
    }

    ~AddMotionStateAnimator()
    {
        node->remove_animator(&motion_anim);
        body->unset_motion_state(&motion_anim);
    }

    static auto create_rule()
    {
        return make_interaction(
                IrrComp::node_attribute,
                PhysComp::node_attribute,
                [](SceneNode* node, RigidBody* body)
                {
                    return new AddMotionStateAnimator(node, body);
                }
        );
    }
};

class Engine
{
private:
    std::vector< std::unique_ptr<Component> > components;
    std::vector< std::unique_ptr<Node>  > nodes;
    std::vector< std::unique_ptr<NodeInteraction> > poss_inter;

public:

    template <typename T>
    Node& add_node(T const& style)
    {
        auto iter_bool = nodes.emplace(node_id, style);
    }
};
