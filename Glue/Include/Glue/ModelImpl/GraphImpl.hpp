#pragma once

#include "ISceneNode.h"

#include "Glue/Model/Graph.hpp"

#include "Glue/Avatar/AvatarComponent.hpp"
#include "Glue/Bullet/BulletComponent.hpp"
#include "Glue/EditorGUI/EditorGUIComponent.hpp"
#include "Glue/Irrlicht/IrrlichtComponent.hpp"

#include <vector>
#include <string>
#include <memory>

namespace Glue {

    class Constraint;  // TODO:  Is this returned from Graph::addConstraint?
//class Structure;  // TODO:  Or should this also manage Constraint's?

    class GraphImpl
    {
    public:

        Node* addNode(NodeStyle const& style);
        Link* addLink(LinkStyle const& style, Node* fromNode, Node* toNode);
        void removeLink(Link* link) const;
        static void registerInteraction(ComponentInteraction* interaction);
        void addComponent(Component* newComp);

        GraphImpl();

        // Deprecated?  Not sure...
        void playSound(std::string const& file);
        void createCamera(Node* lockObj);

        ~GraphImpl();

        void removeConstraint(Constraint* constraint);
        void addConstraint(ConstraintStyle const& style, Node* objA, Node* objB);

        Node* nodeToGameObj(irr::scene::ISceneNode* node) const;

        void removeObj(Node* obj);

        Structure* addStructure(Structure* structure, Structure* leftHandSide);
    };

}
