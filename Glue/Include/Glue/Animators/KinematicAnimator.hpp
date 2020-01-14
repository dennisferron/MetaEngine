// Copyright 2008-2013, 2017 Dennis Ferron

#include "Glue/Animators/MotionStateAnimator.hpp"

namespace Glue {

class KinematicAnimator : public MotionStateAnimator
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

    KinematicAnimator(btTransform const& trans_, btTransform const& centerOfMassOffset_);

    static irr::scene::ISceneNode* watch_node;
    static irr::scene::ISceneNode* get_watch_node() { return watch_node; }
    static void set_watch_node(irr::scene::ISceneNode* value) { watch_node = value; }

private:

    bool init;
    mutable btTransform trans;
    btTransform centerOfMassOffset;
    irr::scene::ISceneNode* cached_node;

    void sync_to_irrlicht() const;
};

}
