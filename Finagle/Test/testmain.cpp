#include "Finagle/Finagle.hpp"

namespace TestFinagle {

using Finagle;

struct Vect
{
    int x;
    int y;
};

struct MotionState
{
    virtual void upd_pos(Vect value) = 0;
};

struct PhysAttr
{
    Vect pos;
    Vect vel;
    MotionState* state;
};

struct Animator
{
    virtual Vect get_pos() const = 0;
};

struct ViewAttr
{
    Animator* anim;
    int color;
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

struct SyncPos
{
    ViewAttr* view;

    SyncPos(PhysAttr* phys, ViewAttr* view)
        : view(view)
    {
        view->pos = [phys](){
            return phys->pos;
        };
    }

    ~SyncPos()
    {
        view->pos = [](){
            return {0, 0};
        };
    }
};

struct GameObjRules
    : protected Rule<SyncPos>
{
    Data<PhysAttr> phys;
    Data<ViewAttr> view;

    GameObjRules() :
        Rule<SyncPos>(phys, view)
    {
    }
};

struct GameObj
{
};

}
