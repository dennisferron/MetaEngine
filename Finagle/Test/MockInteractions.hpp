#pragma once

#include "Finagle/Coupon.hpp"

namespace Mocks {

namespace Interactions {

struct PhysAttr
{
    RigidBody* phys_body;
};

struct PhysComp
{
    PhysWorld world;
    Coupon<PhysAttr> get_attr;
};


struct SceneAttr
{
    SceneNode* scene_node;
};

struct SceneComp
{
    SceneManager* scene_manager;
    Coupon<SceneAttr> get_attr;
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

