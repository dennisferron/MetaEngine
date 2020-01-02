#include "Glue/Model/Node.hpp"

#include <vector>

namespace Glue {

// This list is shared among all Node clones
std::vector<NodeInteraction*> Node::possibleInteractions;

Node::Node(GameObjStyle const& style) :
    graph(nullptr),
    style(style),
    domain()
{
    throw std::logic_error("TODO: implement domain.setSite");
    //domain.setSite(this);
}

Node::~Node()
{
}

Node& Node::setGraph(Graph* value)
{
    throw "TODO:  implement domain.addObject";
//    graph = value;
//    for (auto& c : components)
//        domain.addObject("component", c);
}

void Node::registerInteraction(NodeInteraction* interaction)
{
    possibleInteractions.push_back(interaction);
}

Node& Node::addAttribute(NodeAttribute* attr, NodeInteraction* expectedInteraction)
{
    throw "TODO: implement domain.addObject";
    //domain.addObject("node", attr, expectedInteraction);
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
