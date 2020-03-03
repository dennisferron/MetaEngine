#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Styles/ConstraintStyle.hpp"
#include "ISceneNode.h"

#include "Glue/Model/ITimeComponent.hpp"

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <set>

namespace Glue
{
    class NodeAttribute
    {
    public:
        virtual ~NodeAttribute(){}
    };

    class LinkAttribute
    {
    public:
        virtual ~LinkAttribute() {}
    };

    class ShapeAttribute
    {
    public:
        virtual ~ShapeAttribute() {}
    };

    class IShape
    {
    public:
        virtual ~IShape(){}
        virtual ShapeStyle const& get_style() const = 0;
        virtual void addAttribute(ShapeAttribute* attr) = 0;
        virtual Irrlicht::IIrrlichtShape* get_irrlicht_shape() const = 0;
        virtual Bullet::IBulletShape* get_bullet_shape() const = 0;
    };

    class IGraphObserver
    {
    public:
        virtual ShapeAttribute* addShape(IShape* shape) = 0;
        virtual NodeAttribute* addNode(INode* node) = 0;
        virtual LinkAttribute* addLink(ILink* link) = 0;
    };

    class IStructure
    {
    };

    class INode
    {
    public:
        virtual ~INode()
        {}

        virtual NodeStyle const& get_style() const = 0;

        virtual IShape* get_shape() const = 0;

        virtual void addAttribute(NodeAttribute* attr) = 0;

        virtual Irrlicht::IIrrlichtAttribute* get_irrlicht_attribute() const = 0;

        virtual Bullet::IBulletAttribute* get_bullet_attribute() const = 0;

        virtual Avatar::IAvatarAttribute* get_avatar_attribute() const = 0;
    };

    class ILink
    {
    public:
        virtual ~ILink()
        {}

        virtual LinkStyle const& get_style() const = 0;

        virtual void addAttribute(LinkAttribute* attr) = 0;

        virtual INode* get_fromNode() const = 0;

        virtual INode* get_toNode() const = 0;
    };

    class IGraph
    {
    public:

        virtual ~IGraph()
        {}

        virtual void addComponent(IGraphObserver* component) = 0;

        virtual IShape* addShape(ShapeStyle const& style) = 0;

        virtual INode* addNode(NodeStyle const& style, IShape* shape) = 0;

        virtual ILink* addLink(LinkStyle const& style, INode* fromNode, INode* toNode) = 0;

        virtual void removeLink(ILink* link) const = 0;

        virtual void playSound(std::string const& file) = 0;

        virtual void createCamera(INode* lockObj) = 0;

        virtual INode* nodeToGameObj(irr::scene::ISceneNode* node) const = 0;

        virtual void removeObj(INode* obj) = 0;

        virtual IStructure* addStructure(IStructure* structure, IStructure* leftHandSide) = 0;
    };
}
