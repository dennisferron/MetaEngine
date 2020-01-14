#include "Glue/Model/Node.hpp"

#include <vector>

namespace Glue {

// This list is shared among all Node clones
std::vector<NodeInteraction*> Node::possibleInteractions;

Node::Node(GameObjStyle const& style) :
    style(style),
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
    return irrlicht_attribute;
}

Glue::Bullet::BulletAttribute* Node::get_bullet_attribute() const
{
    return bullet_attribute;
}

Glue::Avatar::AvatarAttribute* Node::get_avatar_attribute() const
{
    return avatar_attribute;
}

    void Node::addAttribute(Glue::Irrlicht::IrrlichtAttribute* attr)
    {
        irrlicht_attribute = attr;
        // TODO: manage motion state
    }

    void Node::addAttribute(Glue::Bullet::BulletAttribute* attr)
    {
        bullet_attribute = attr;
        // TODO: manage motion state
    }

    void Node::addAttribute(Glue::Avatar::AvatarAttribute* attr)
    {
        avatar_attribute = attr;
    }

    void Node::addAttribute(Glue::Avatar::Camera* attr)
    {
        avatar_camera = attr;
    }

} // namespace Glue
