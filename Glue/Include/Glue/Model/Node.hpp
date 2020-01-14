#pragma once

#include "Glue/Model/Domain.hpp"
#include "Glue/Interactions/Node/NodeInteraction.hpp"
#include "Glue/Styles/GameObjStyle.hpp"

#include "Glue/Irrlicht/IrrlichtAttribute.hpp"
#include "Glue/Bullet/BulletAttribute.hpp"

#include <vector>
#include <Glue/Avatar/AvatarComponent.hpp>
#include <Glue/Avatar/AvatarAttribute.hpp>
#include <Glue/Avatar/Camera.hpp>

namespace Glue {

class Node
{
private:
    NodeStyle style;

    Glue::Irrlicht::IrrlichtAttribute* irrlicht_attribute = nullptr;
    Glue::Bullet::BulletAttribute* bullet_attribute = nullptr;
    Glue::Avatar::AvatarAttribute* avatar_attribute = nullptr;
    Glue::Avatar::Camera* avatar_camera = nullptr;

public:

    Node(NodeStyle const& style);
    ~Node();

    NodeStyle const& get_style() const;

    Glue::Irrlicht::IrrlichtAttribute* get_irrlicht_attribute() const;
    Glue::Bullet::BulletAttribute* get_bullet_attribute() const;
    Glue::Avatar::AvatarAttribute* get_avatar_attribute() const;

    void addAttribute(Glue::Irrlicht::IrrlichtAttribute* attr);
    void addAttribute(Glue::Bullet::BulletAttribute* attr);
    void addAttribute(Glue::Avatar::AvatarAttribute* attr);
    void addAttribute(Glue::Avatar::Camera* attr);
};

}
