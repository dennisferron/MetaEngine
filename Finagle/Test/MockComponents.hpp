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

}

namespace Graphics {

struct Animator
{
    virtual Vect get_pos() const = 0;
};

struct SceneNode
{
    Animator* anim;
    int color;
};

}

}
