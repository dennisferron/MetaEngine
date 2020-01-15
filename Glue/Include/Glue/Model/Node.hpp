#pragma once

#include "Glue/Model/Domain.hpp"
#include "Glue/Interactions/Node/NodeInteraction.hpp"
#include "Glue/Styles/GameObjStyle.hpp"

#include "Glue/Irrlicht/IrrlichtAttribute.hpp"
#include "Glue/Bullet/BulletAttribute.hpp"
#include "Glue/Animators/MotionStateAnimator.hpp"

#include <vector>
#include <Glue/Avatar/AvatarComponent.hpp>
#include <Glue/Avatar/AvatarAttribute.hpp>
#include <Glue/Avatar/Camera.hpp>

#include <memory>

namespace Glue {

class Node
{
private:
    NodeStyle style;
    MotionStateAnimator* motionState;

    std::unique_ptr<Glue::Irrlicht::IrrlichtAttribute> irrlicht_attribute;
    std::unique_ptr<Glue::Bullet::BulletAttribute> bullet_attribute;
    std::unique_ptr<Glue::Avatar::AvatarAttribute> avatar_attribute;
    std::unique_ptr<Glue::Avatar::Camera> avatar_camera;

public:

    Node(NodeStyle const& style);
    ~Node();

    NodeStyle const& get_style() const;

    Glue::Irrlicht::IrrlichtAttribute* get_irrlicht_attribute() const;
    Glue::Bullet::BulletAttribute* get_bullet_attribute() const;
    Glue::Avatar::AvatarAttribute* get_avatar_attribute() const;

    void addAttribute(std::unique_ptr<Glue::Irrlicht::IrrlichtAttribute>&& attr);
    void addAttribute(std::unique_ptr<Glue::Bullet::BulletAttribute>&& attr);
    void addAttribute(std::unique_ptr<Glue::Avatar::AvatarAttribute>&& attr);
    void addAttribute(std::unique_ptr<Glue::Avatar::Camera>&& attr);
};

}
