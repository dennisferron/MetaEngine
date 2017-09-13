#include "Finagle/Finagle.hpp"

namespace TestFinagle {

using Finagle;

struct Vect
{
    int x;
    int y;
};

struct PhysAttr
{
    Vect pos;
    Vect vel;
};

struct ViewAttr
{
    std::function<Vect()> pos;
    int color;
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
