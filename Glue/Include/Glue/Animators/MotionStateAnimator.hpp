// Copyright 2008-2020 Dennis Ferron

#pragma once

#include "btBulletDynamicsCommon.h"
#include "irrlicht.h"

namespace Glue
{

    class MotionStateAnimator : public btMotionState, public irr::scene::ISceneNodeAnimator
    {
    };

}
