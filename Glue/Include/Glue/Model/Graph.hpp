#pragma once

#include <vector>
#include <string>

namespace MetaEngine {

class RootModule;

}

namespace MetaEngine { namespace Styles {

class GameObjStyle;  // Todo: rename to NodeStyle
using NodeStyle = GameObjStyle;
class LinkStyle;    // Todo:  investigate if can merge with ConstraintStyle
class ConstraintStyle;

}}

namespace MetaEngine {

class Component;
class Domain;
class Interaction;
class Node;
class Link;

class Graph
{
private:
    std::vector<Component*> components;
	Domain domain;

    // possible interactions shared among all instances
    static std::vector<Interaction*> possibleInteractions;

    Node* addNode(NodeStyle const& style);
    Link* addLink(LinkStyle const& style, Node* fromNode, Node* toNode);
    void removeLink(Link* link) const;
    void registerInteraction(Interaction* interaction);
    void addComponent(Component* newComp, Interaction* expectedInteraction);

    Graph();

    // Deprecated?  Not sure...
    void playSound(std::string const& file);
    void createCamera(Node* lockObj);

    ~Graph();

    void removeConstraint(Constraint* constraint);
    void addConstraint(ConstraintStyle const& style, Node* objA, Node* objB);

    Node* nodeToGameObj(irr::Scene::ISceneNode* node) const;

    void removeObj(Node* obj);

    Structure* addStructure(Structure* structure, Structure* leftHandSide);
};

}
