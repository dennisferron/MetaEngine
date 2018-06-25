#include <vector>
#include <iostream>

class Scope;

class Identity
{
private:
    Scope const* scope;
    int id_val;

    friend class Scope;

    Identity(Scope const* scope, int id_val)
        : scope(scope), id_val(id_val)
    {
    }

public:
    friend bool operator ==(Identity const& x, Identity const& y)
    {
        return (x.scope == y.scope) && (x.id_val == y.id_val);
    }

    friend bool operator <(Identity const& x, Identity const& y)
    {
        return (x.scope == y.scope) ? (x.id_val < y.id_val) : (x.scope < y.scope);
    }
};

class Scope
{
private:
    int id_counter;

public:

    Scope() : id_counter(0) {}

    Identity operator ++()
    {
        return { this, id_counter++ };
    }
};

template <typename T>
class symbol
{
private:
    Identity id;

public:
    symbol(Identity id) : id(id) {}

    friend bool operator ==(symbol<T> const& x, symbol<T> const& y)
    {
        return x.id == y.id;
    }

    friend bool operator <(symbol<T> const& x, symbol<T> const& y)
    {
        return x.id < y.id;
    }
};

Scope global_scope;

struct NodeStyle
{
};

struct BallStyle
{
    static symbol<BallStyle> style_id;

    double radius;
};

symbol<BallStyle> BallStyle::style_id(global_scope++);

struct BoxStyle
{
    static symbol<BoxStyle> style_id;

    double xs;
    double ys;
    double zs;
};

symbol<BoxStyle> BoxStyle::style_id(global_scope++);

class NodeInteraction
{
private:
public:
    ~NodeInteraction() = 0;
};

NodeInteraction::~NodeInteraction() {}

class Node
{
private:
    computation<Node> comp;
    std::unique_ptr<NodeStyle> style;
    std::map< Identity , std::unique_ptr<NodeInteraction const> > interactions;

public:

    template <typename T>
    Node(T const& style) : comp(this), std::make_unique<T>(style)
    {
        comp[T::style_id] = *(this->style);
    }

    void add_interaction(NodeInteraction const* interaction);

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
    std::map< symbol<Node> , std::unique_ptr<SceneNode> > scene_nodes;

public:
    static symbol<SceneNode> node_attribute;
};

symbol<SceneNode> IrrComp::node_attribute = global_scope++;

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
    std::map< symbol<Node> , RigidBody > bodies;

public:
    static symbol<RigidBody> node_attribute;

};

symbol<RigidBody> PhysComp::node_attribute = global_scope++;


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
    Scope scope;
    std::map< symbol<Component>,  std::unique_ptr<Component>  > components;
    std::map< symbol<Node>,  std::unique_ptr<Node>  > nodes;
    std::map< symbol<NodeInteraction>, std::unique_ptr<NodeInteraction>  > poss_inter;

public:

    template <typename T>
    Node& add_node(T const& style)
    {
        Identity node_id = scope++;
        auto iter_bool = nodes.emplace(node_id, style);

    }
};


void do_test()
{
    BallStyle a_ball;
    BoxStyle a_box;

    Engine engine;
    Node& n0 = engine.add_node(a_ball);
    Node& n1 = engine.add_node(a_box);
}
