#include "Glue/Model/Node.hpp"

#include <vector>

namespace Glue
{

Node::Node(NodeStyle const& style) :
    style(style)
{
}

Node::~Node()
{
}

NodeStyle const& NodeStyle::get_style() const
{
    return style;
}

Glue::Irrlicht::IrrlichtAttribute* Node::get_irrlicht_attribute() const
{
    return irrlicht_attribute.get();
}

Glue::Bullet::BulletAttribute* Node::get_bullet_attribute() const
{
    return bullet_attribute.get();
}

Glue::Avatar::AvatarAttribute* Node::get_avatar_attribute() const
{
    return avatar_attribute.get();
}

    void Node::addAttribute(std::unique_ptr<Glue::Irrlicht::IrrlichtAttribute>&& attr)
    {
        irrlicht_attribute = std::move(attr);

        if (irrlicht_attribute && motionState)
        {
            irrlicht_attribute->setMotionState(motionState);
        }
    }

    void Node::addAttribute(std::unique_ptr<Glue::Bullet::BulletAttribute>&& attr)
    {
        bullet_attribute = std::move(attr);

        motionState = static_cast<MotionStateAnimator*>(
                bullet_attribute->getRigidBody().getMotionState());

        if (irrlicht_attribute && motionState)
        {
            irrlicht_attribute->setMotionState(motionState);
        }
    }

    void Node::addAttribute(std::unique_ptr<Glue::Avatar::AvatarAttribute>&& attr)
    {
        avatar_attribute = std::move(attr);
    }

    void Node::addAttribute(std::unique_ptr<Glue::Avatar::Camera>&& attr)
    {
        avatar_camera = std::move(attr);
    }

} // namespace Glue
