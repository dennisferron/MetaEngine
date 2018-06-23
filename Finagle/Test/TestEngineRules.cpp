#include <vector>

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

template <typename... Ts>
class relation
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
    ~NodeInteraction() = 0;
};

NodeInteraction::~NodeInteraction() {}

class Node
{
private:
    Scope scope;

    std::map< Identity , std::unique_ptr<NodeInteraction const> > interactions;

public:

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
};

class IrrComp : public Component
{
private:
    std::map< symbol<Node> , std::unique_ptr<SceneNode> > scene_nodes;

public:

};

class MotionState
{
};

class RigidBody
{
};

class PhysComp : public Component
{
private:
    std::map< symbol<Node> , RigidBody > bodies;
};

class MotionStateAnimator : public MotionState, public Animator
{
};

class Engine
{
private:
    Scope scope;
    std::map<Identity,  std::unique_ptr<Component>  > components;
    std::map<Identity, Node> nodes;
    relation<Node, NodeInteraction> poss_inter;

public:


};


void do_test()
{

}
