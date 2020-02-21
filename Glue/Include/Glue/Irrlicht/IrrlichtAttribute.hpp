#pragma once

#include <functional>
#include <Glue/Styles/GameObjStyle.hpp>

#include "IMesh.h"
#include "ITexture.h"
#include "ISceneNode.h"
#include "ISceneNodeAnimator.h"

#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"

namespace Glue
{
    class Node;
}

namespace Glue::Irrlicht
{

    class IrrlichtAttribute : public IIrrlichtAttribute
    {
    private:

        NodeStyle style;
        irr::video::ITexture* texture;
        irr::scene::ISceneNode* sceneNode;
        irr::scene::ISceneNodeAnimator* motionState;
        irr::scene::IMesh* dispShape;
        int flagBits;
        bool isMouseDraggable;

        void setFlagBit(int pos, bool state);

    public:
        IrrlichtAttribute(NodeStyle const& style, irr::scene::ISceneNode* sceneNode);
        ~IrrlichtAttribute();
        void setMotionState(irr::scene::ISceneNodeAnimator* value) final;
        void setDispShape(irr::scene::IMesh* value) final;
        void setIsMouseDraggable(bool state = true) final;
        void addKinematicAnimator(irr::scene::ISceneNodeAnimator* anim) final;
        void addChild(IIrrlichtAttribute* otherObj) final;
        irr::core::vector3df getPos() const final;
        void triggerAllGenerators(std::function<void(INode*)> onTrigger) final;
        void lockTo(INode* otherObj) final;
        irr::scene::ISceneNode* getSceneNode() const { return sceneNode; }
    };

}
