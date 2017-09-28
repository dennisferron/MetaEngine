#pragma once

#include "MockComponents.hpp"

namespace Mocks {


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
