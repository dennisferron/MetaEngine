#include "Glue/Model/Node.hpp"

#include "Glue/Utility/variant_helpers.hpp"

namespace Glue
{

Node::Node(NodeStyle const& style, IShape* shape) :
    style(style), shape(shape)
{
}

Node::~Node()
{
}

NodeStyle const& Node::get_style() const
{
    return style;
}

IShape* Node::get_shape() const
{
    return shape;
}

Irrlicht::IIrrlichtAttribute* Node::get_irrlicht_attribute() const
{
    return find_attribute<Irrlicht::IIrrlichtAttribute>(attributes);
}

Bullet::IBulletAttribute* Node::get_bullet_attribute() const
{
    return find_attribute<Bullet::IBulletAttribute>(attributes);
}

Avatar::IAvatarAttribute* Node::get_avatar_attribute() const
{
    return find_attribute<Avatar::IAvatarAttribute>(attributes);
}

    void Node::addAttribute(NodeAttribute attr)
    {
        // TODO:  Handle interactions; only push_back after that.
        attributes.push_back(attr);
    }

} // namespace Glue
