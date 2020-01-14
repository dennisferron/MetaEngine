// Copyright 2008-2020 Dennis Ferron

#include "Glue/Animators/MotionStateAnimator.hpp"

namespace Glue {

class LockAnimator : public MotionStateAnimator
{
public:

    // Bullet stuff
    virtual void setWorldTransform(btTransform const& worldTrans);
    virtual void getWorldTransform(btTransform& worldTrans) const;

    // Irrlicht stuff
    virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
    virtual irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node,
                    irr::scene::ISceneManager* newManager=0);
    irr::scene::ESCENE_NODE_ANIMATOR_TYPE getType() const;

    LockAnimator(btMotionState* target_,
            btTransform const& centerOfMassOffset_);

    bool stop_rotation;

private:

    btMotionState* target;
    mutable btTransform trans;
    btTransform centerOfMassOffset;
};

}
