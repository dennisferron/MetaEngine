#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Animators/MotionStateAnimator.hpp"

#include <vector>
#include <Glue/Avatar/AvatarComponent.hpp>
#include <Glue/Avatar/AvatarAttribute.hpp>
#include <Glue/Avatar/Camera.hpp>

#include <memory>

namespace Glue
{
    // Visitor for NodeAttribute
    class NodeInteractions
    {
        // TODO:  Add member variables for interactions.
    };

class Node : public INode
{
private:
    NodeStyle style;
    IShape* shape;
    NodeInteractions interactions;
    std::vector<NodeAttribute> attributes;

public:

    Node(NodeStyle const& style, IShape* shape);
    ~Node();

    IShape* get_shape() const final;
    NodeStyle const& get_style() const final;
    void addAttribute(NodeAttribute attr) final;

    Irrlicht::IIrrlichtAttribute* get_irrlicht_attribute() const final;
    Bullet::IBulletAttribute* get_bullet_attribute() const final;
    Avatar::IAvatarAttribute* get_avatar_attribute() const final;
};

}
