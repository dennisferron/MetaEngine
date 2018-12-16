#pragma once

#include <functional>

#include "IMesh.h"
#include "ITexture.h"
#include "ISceneNode.h"
#include "ISceneNodeAnimator.h"

namespace Glue { namespace Irrlicht {

class Node;
class GameObjStyle;

class NodeAttribute
{
private:

    GameObjStyle* style;
    irr::video::ITexture* texture;
    irr::scene::ISceneNode* sceneNode;
    irr::scene::ISceneNodeAnimator* motionState;
    irr::scene::IMesh* dispShape;
    int flagBits;
    bool isMouseDraggable;

    NodeAttribute& setFlagBit(int pos, bool state);

public:

    NodeAttribute& setMotionState(irr::scene::ISceneNodeAnimator* value);
    NodeAttribute& setDispShape(irr::scene::IMesh* value);
    NodeAttribute& setIsMouseDraggable(bool state=true);

    void addKinematicAnimator(irr::scene::ISceneNodeAnimator* anim);
    void addChild(NodeAttribute* otherObj);

    irr::core::vector3df getPos() const;

    void triggerAllGenerators(std::function<void(Node*)> onTrigger);

    void lockTo(Node* otherObj);

    ~NodeAttribute();
};

}}
