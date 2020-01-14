// Copyright 2008-2013, 2017 Dennis Ferron

#include "Glue/Animators/LockAnimator.hpp"
#include "Glue/Animators/CustomAnimatorTypes.hpp"

#include <stdexcept>

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

namespace Glue {

LockAnimator::LockAnimator(btMotionState* target_, btTransform const& centerOfMassOffset_)
    : stop_rotation(true), target(target_), centerOfMassOffset(centerOfMassOffset_) {}

ESCENE_NODE_ANIMATOR_TYPE LockAnimator::getType() const
{
    return static_cast<ESCENE_NODE_ANIMATOR_TYPE>(C_ESNAT_LOCK);
}

void LockAnimator::setWorldTransform(btTransform const& worldTrans)
{
    trans = worldTrans;
}

void LockAnimator::getWorldTransform(btTransform& worldTrans) const
{
    btTransform targetTransform;
    target->getWorldTransform(targetTransform);

    trans.setOrigin(targetTransform.getOrigin());

    if (stop_rotation)
        trans.setRotation(btQuaternion::getIdentity());
    else
        trans.setRotation(targetTransform.getRotation());

    worldTrans = trans;
}


void LockAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
    // We don't care about the timeMs value here; bullet is handling that.

    irr::core::matrix4 matr;
    trans.getOpenGLMatrix(matr.pointer());
    node->setRotation(matr.getRotationDegrees());
    node->setPosition(matr.getTranslation());

}


ISceneNodeAnimator* LockAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
{
    throw std::runtime_error("createClone for irrlicht not implemented yet because I'm not sure how/whether the physics object gets cloned.");
}

}
