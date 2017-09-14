#pragma once

#include "MockComponents.hpp"

namespace NodeSyncTest {

struct MotionStateAnimator
    : public MotionState, public Animator
{
    Vect cached_pos;
    void upd_pos(Vect value) override
        { cached_pos = value; }
    Vect get_pos() const override
        { return cached_pos; }
};

struct PhysAttr
{
    RigidBody* phys_body;
};

struct SceneAttr
{
    SceneNode* scene_node;
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
