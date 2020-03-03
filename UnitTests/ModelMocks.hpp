#pragma once

#include "Glue/Model/ModelInterfaces.hpp"

namespace
{
    using namespace Glue;
    
    class MockShape : public IShape
    {
    public:
        ShapeStyle style;

        ShapeStyle const& get_style() const override { return style; }
        void addAttribute(ShapeAttribute* attr) override{}
        Irrlicht::IIrrlichtShape* get_irrlicht_shape() const override { return nullptr;}
        Bullet::IBulletShape* get_bullet_shape() const override{ return nullptr;}
    };

    class MockGraphObserver : public IGraphObserver
    {
    public:
        ShapeAttribute* addShape(IShape* shape) override{ return nullptr; }
        NodeAttribute* addNode(INode* node) override{return nullptr;}
        LinkAttribute* addLink(ILink* link) override{return nullptr;}
    };

    class MockStructure : public IStructure
    {
    };

    class MockNode : public INode
    {
    public:
        NodeStyle style;

        NodeStyle const& get_style() const override{ style;}

        IShape* get_shape() const override{ return nullptr;}

        void addAttribute(NodeAttribute* attr) override{}

        Irrlicht::IIrrlichtAttribute* get_irrlicht_attribute() const override{ return nullptr; }

        Bullet::IBulletAttribute* get_bullet_attribute() const override{ return nullptr; }

        Avatar::IAvatarAttribute* get_avatar_attribute() const override{ return nullptr; }
    };

    class MockLink : public ILink
    {
    public:
        LinkStyle style;

        LinkStyle const& get_style() const override{ return style;}

        void addAttribute(LinkAttribute* attr) override{}

        INode* get_fromNode() const override{ return nullptr;}

        INode* get_toNode() const override{ return nullptr;}
    };

    class MockGraph : public IGraph
    {
    public:
        void addComponent(IGraphObserver* component) override{}

        IShape* addShape(ShapeStyle const& style) override{ return nullptr;}

        INode* addNode(NodeStyle const& style, IShape* shape) override{return nullptr;}

        ILink* addLink(LinkStyle const& style, INode* fromNode, INode* toNode) override{return nullptr;}

        void removeLink(ILink* link) const override{}

        void playSound(std::string const& file) override{}

        void createCamera(INode* lockObj) override{}

        INode* nodeToGameObj(irr::scene::ISceneNode* node) const override{return nullptr;}

        void removeObj(INode* obj) override{}

        IStructure* addStructure(IStructure* structure, IStructure* leftHandSide) override{return nullptr;}
    };
}