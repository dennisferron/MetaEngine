#pragma once

#include "ITimer.h"
#include "ISceneNode.h"


#include <string>

namespace Glue
{
    class INode;
    class IGraph;
}

namespace Glue::Irrlicht
{
    class IIrrlichtAttribute;

    class IIrrlichtComponent
    {
    public:

        virtual ~IIrrlichtComponent()
        {}

        virtual irr::ITimer* get_deviceTimer() = 0;

        virtual IIrrlichtAttribute* addNode(INode* node) = 0;

        virtual void playSound(std::string const& file) = 0;

        virtual void beforeGraphics() = 0;

        virtual void onGraphics(Scalar timeElapsed) = 0;

        virtual void afterGraphics() = 0;

        virtual bool shouldRun() const = 0;

        virtual INode* nodeToGameObj(irr::scene::ISceneNode*) = 0;

        virtual void removeObj(INode* obj) = 0;
    };

    class IIrrlichtAttribute
    {
    public:
        virtual ~IIrrlichtAttribute()
        {};

        virtual void setMotionState(irr::scene::ISceneNodeAnimator* value) = 0;

        virtual void setDispShape(irr::scene::IMesh* value) = 0;

        virtual void setIsMouseDraggable(bool state = true) = 0;

        virtual void addKinematicAnimator(irr::scene::ISceneNodeAnimator* anim) = 0;

        virtual void addChild(IIrrlichtAttribute* otherObj) = 0;

        virtual irr::core::vector3df getPos() const = 0;

        virtual void triggerAllGenerators(std::function<void(INode*)> onTrigger) = 0;

        virtual void lockTo(INode* otherObj) = 0;

        virtual irr::scene::ISceneNode* getSceneNode() const = 0;
    };
}
