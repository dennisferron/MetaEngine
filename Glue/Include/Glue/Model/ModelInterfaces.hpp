#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Styles/ConstraintStyle.hpp"
#include "ISceneNode.h"


#include <vector>
#include <string>
#include <memory>
#include <variant>

namespace Glue
{
    namespace Avatar
    {
        class IAvatarComponent;
        class IAvatarAttribute;
        class IAvatarCamera;
    }

    namespace Irrlicht
    {
        class IIrrlichtComponent;
        class IIrrlichtAttribute;
    }

    namespace Bullet
    {
        class IBulletAttribute;
        class IBulletComponent;
    }

    using NodeAttribute = std::variant<
            Avatar::IAvatarAttribute*,
            Irrlicht::IIrrlichtAttribute*,
            Bullet::IBulletAttribute*>;

    using LinkAttribute = std::variant<
            void*
            >;

    using GraphComponent = std::variant<
            Avatar::IAvatarComponent*,
            Irrlicht::IIrrlichtComponent*,
            Bullet::IBulletComponent*>;

	class IStructure
    {
    };

	// TODO:  If all of the components and attributes use interfaces,
	// maybe the Model doesn't need have interfaces.
	//
	// The higher level objects should forward declare the lower level ones
	// that they use, so that code which uses only a subset of the components
	// doesn't need to reference anything from the components or attributes not used.
	
	class INode
	{
	public:
	    virtual ~INode() {}
		virtual NodeStyle const& get_style() const = 0;
		virtual void addAttribute(NodeAttribute attr) = 0;
		virtual Bullet::IBulletAttribute* get_bullet_attribute() = 0;
        virtual Irrlicht::IIrrlichtAttribute* get_irrlicht_attribute() const = 0;
        virtual Bullet::IBulletAttribute* get_bullet_attribute() const = 0;
        virtual Avatar::IAvatarAttribute* get_avatar_attribute() const = 0;
	};

    class ILink
    {
    public:
        virtual ~ILink() {}
        virtual LinkStyle const& get_style() const = 0;
        virtual void addAttribute(LinkAttribute attr) = 0;
        virtual INode* get_fromNode() const = 0;
        virtual INode* get_toNode() const = 0;
    };

    class IGraph
    {
    public:

        virtual ~IGraph() {}
        virtual INode* addNode(NodeStyle const& style) = 0;
        virtual ILink* addLink(LinkStyle const& style, INode* fromNode, INode* toNode) = 0;
        virtual void removeLink(ILink* link) const = 0;
        virtual void playSound(std::string const& file) = 0;
        virtual void createCamera(INode* lockObj) = 0;
        virtual INode* nodeToGameObj(irr::scene::ISceneNode* node) const = 0;
        virtual void removeObj(INode* obj) = 0;
        virtual IStructure* addStructure(IStructure* structure, IStructure* leftHandSide) = 0;
    };

    enum class EventWhen
    {
        before,
        on,
        after
    };

    enum class EventWhat
    {
        frame,
        physics,
        graphics
    };

    using RelTime = Scalar;
    using AbsTime = Scalar;

    struct TimeInfo
    {
        RelTime delta;
        AbsTime current;
        AbsTime last;
    };

    struct EngineEvent
    {
        EventWhen when;
        EventWhat what;
        std::function<void(TimeInfo)> action;
    };

    struct TimeoutEvent
    {
        AbsTime fromTime;
        AbsTime atTime;
        std::function<RelTime(RelTime)> action;

        bool operator<(TimeoutEvent const& that) const
        {
            return this->atTime < that.atTime;
        }

        bool operator<=(AbsTime const& nowTime) const
        {
            return this->atTime <= nowTime;
        }
    };


    class ITimeComponent
    {
    public:
        virtual ~ITimeComponent() {}
        virtual void setTimeout(RelTime delay, std::function<RelTime(RelTime)> action) = 0;
        virtual RelTime elapsed() const = 0;
        virtual void runLoop() = 0;
        virtual void add_handler(EventWhen when, EventWhat what, std::function<void(TimeInfo)> action) = 0;
    };
}
