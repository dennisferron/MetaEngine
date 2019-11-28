#include "Glue/Irrlicht/IrrlichtAttribute.hpp"

namespace Glue { namespace Irrlicht {

        void IrrlichtAttribute::setFlagBit(int pos, bool state)
        {
            throw "Not implemented";
        }

        void IrrlichtAttribute::setMotionState(irr::scene::ISceneNodeAnimator* value)
        {
            throw "Not implemented";

        }

        void IrrlichtAttribute::setDispShape(irr::scene::IMesh* value)
        {
            throw "Not implemented";

        }

        void IrrlichtAttribute::setIsMouseDraggable(bool state)
        {
            throw "Not implemented";

        }

        void IrrlichtAttribute::addKinematicAnimator(irr::scene::ISceneNodeAnimator* anim)
        {
            throw "Not implemented";

        }

        void IrrlichtAttribute::addChild(IrrlichtAttribute* otherObj)
        {

            throw "Not implemented";
        }

        irr::core::vector3df IrrlichtAttribute::getPos() const
        {
            throw "Not implemented";

        }

        void IrrlichtAttribute::triggerAllGenerators(std::function<void(Node*)> onTrigger)
        {
            throw "Not implemented";

        }

        void IrrlichtAttribute::lockTo(Node* otherObj)
        {
            throw "Not implemented";

        }

        IrrlichtAttribute::~IrrlichtAttribute()
        {
        }

//        style ::= nil
//        texture ::= nil
//        sceneNode ::= nil
//
//        motionState := nil
//        setMotionState := method(value,
//            motionState = value
//            if(motionState != nil,
//                if(sceneNode != nil,
//                    sceneNode addAnimator(motionState)
//                )
//            )
//        )
//
//        dispShape ::= nil
//        flagBits ::= nil
//
//        isMouseDraggable := nil
//        setIsMouseDraggable := method(state,
//            if(state==nil,
//                state = (style mass != 0)
//            )
//            isMouseDraggable = state
//            if(flagBits != nil and sceneNode != nil,
//                flagBits setBit(Constants mouseDraggableBitPos, state)
//            )
//            self
//        )
//
//        setFlagBit := method(pos, state,
//            flagBits setBit(pos, state)
//            self
//        )
//
//        addKinematicAnimator := method(anim,
//            animators append(anim)
//            sceneNode addAnimator(anim)
//        )
//
//        addChild := method(otherObj,
//            sceneNode addChild(otherObj sceneNode)
//        )
//
//        getPos := method(
//            if (sceneNode != nil) then(
//                p := sceneNode getAbsolutePosition
//                o := Object clone
//                o x := p get_X; o y := p get_Y; o z := -p get_Z
//                return o
//            )
//            else(
//                return style getPos
//            )
//        )
//
//        triggerAllGenerators := method(onTrigger,
//            if (style hasSlot("spawnStyle"),
//                s := style spawnStyle clone
//                s setPos(s x + getX, s y + getY, s z + getZ)
//                // TODO:  Set relative velocity as well as pos.
//                obj := engine addObj(s)
//
//                if(onTrigger != nil, onTrigger call(obj))
//            )
//            childObjs foreach(o, o triggerAllGenerators(onTrigger))
//        )
//
//        lockTo := method(otherObj,
//
//            oldMotionState := motionState
//            setMotionState(
//                LockAnimator new(otherObj rigidBody getMotionState_c, namespace Bullet getIdentityTransform)
//            )
//
//            if (sceneNode != nil,
//                sceneNode addAnimator(motionState)
//                sceneNode removeAnimator(oldMotionState)
//            )
//
//            oldMotionState drop
//
//            motionState
//        )
//
//        dispose := method(
//            sceneNode remove
//            //sceneNode drop
//        )
//    )
//)

}}
