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

class Graph;
class Interaction;

class NodeAttribute
{
};

class Node
{
public:
    Graph* graph;
    GameObjStyle style;
    Domain* domain;

    // This list is shared among all Link clones
    static std::vector<NodeInteraction*> possibleInteractions;

    static void registerInteraction(NodeInteraction* interaction);

private:

    Glue::Irrlicht::IrrlichtAttribute* irrlicht_attribute = nullptr;
    Glue::Bullet::BulletAttribute* bullet_attribute = nullptr;
    Glue::Avatar::AvatarAttribute* avatar_attribute = nullptr;
    Glue::Avatar::Camera* avatar_camera = nullptr;

public:

    Node(GameObjStyle const& style);
    ~Node();

    Glue::Irrlicht::IrrlichtAttribute* get_irrlicht_attribute() const;
    Glue::Bullet::BulletAttribute* get_bullet_attribute() const;
    Glue::Avatar::AvatarAttribute* get_avatar_attribute() const;

    Node& setGraph(Graph* value);
    Node& addAttribute(NodeAttribute* attr, NodeInteraction* expectedInteraction);

    void addAttribute(Glue::Irrlicht::IrrlichtAttribute* attr);
    void addAttribute(Glue::Bullet::BulletAttribute* attr);
    void addAttribute(Glue::Avatar::AvatarAttribute* attr);
    void addAttribute(Glue::Avatar::Camera* attr);

    /*
    template <typename T>
    T* findAttribute() const
    {
        return domain->findObject<T>(DomainObjects::node);
    )
    */
};

}
