#pragma once

namespace Mocks {

namespace Common {

struct Vect
{
    int x;
    int y;
};

}

namespace Physics {

struct MotionState
{
    virtual void upd_pos(Vect value) = 0;
};

struct RigidBody
{
    Vect pos;
    Vect vel;
    MotionState* state;
};

struct PhysWorld
{
    std::vector<RigidBody> objs;
};

}

namespace Graphics {

struct Animator
{
    virtual Vect get_pos() const = 0;
};

struct SceneNode
{
    Animator* anim;
    std::string name;
};

struct SceneManager
{
    std::vector<SceneNode*> nodes;
};

}

namespace Interactions {

struct SceneAttr
{
    SceneNode* scene_node;
};

struct SceneComp
{
    SceneManager* scene_manager;
};

struct MotionStateAnimator
    : public MotionState, public Animator
{
    Vect cached_pos;
    void upd_pos(Vect value) override
        { cached_pos = value; }
    Vect get_pos() const override
        { return cached_pos; }
};

}

}
