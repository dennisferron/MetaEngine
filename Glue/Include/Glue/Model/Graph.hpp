#pragma once

#include "ISceneNode.h"

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Styles/ConstraintStyle.hpp"
#include "Glue/Model/Domain.hpp"
#include "Glue/Model/Interaction.hpp"
#include "Glue/Model/Node.hpp"
#include "Glue/Model/Link.hpp"
#include "Glue/Model/Structure.hpp"
#include "Glue/Model/Component.hpp"
#include "Glue/Interactions/Component/ComponentInteraction.hpp"

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

    class Graph
    {
    private:
        Bullet::BulletComponent blt_cmp;
        Irrlicht::IrrlichtComponent irr_cmp;

        std::vector<Node*> nodes;

    public:

        Node *addNode(NodeStyle const &style);

        Link *addLink(LinkStyle const &style, Node *fromNode, Node *toNode);

        void removeLink(Link *link) const;

        static void registerInteraction(ComponentInteraction *interaction);

        void addComponent(Component *newComp);

        Graph();

        // Deprecated?  Not sure...
        void playSound(std::string const &file);

        void createCamera(Node *lockObj);

        ~Graph();

        void removeConstraint(Constraint *constraint);

        void addConstraint(ConstraintStyle const &style, Node *objA, Node *objB);

        Node *nodeToGameObj(irr::scene::ISceneNode *node) const;

        void removeObj(Node *obj);

        Structure *addStructure(Structure *structure, Structure *leftHandSide);
    };

}
