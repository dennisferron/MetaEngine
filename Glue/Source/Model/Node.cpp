#include "Glue/Model/Node.hpp"

#include <vector>

namespace
{
    template <typename T>
    struct AttributeFinder
    {
        T* result = nullptr;

        void operator()(T* value)
        {
            if (result)
                throw std::logic_error("More than one attribute of this type is present.");

            result = value;
        }

        template <typename U>
        void operator()(U*)
        {
            // do nothing
        }
    };

    template <typename T>
    T* find_attribute(std::vector<Glue::NodeAttribute> const& attrs)
    {
        AttributeFinder<T> v;
        for (auto a : attrs)
            std::visit(v, a);
        return v.result;
    }
}

namespace Glue
{

Node::Node(NodeStyle const& style) :
    style(style)
{
}

Node::~Node()
{
}

NodeStyle const& Node::get_style() const
{
    return style;
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
