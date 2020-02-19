#pragma once

#include "ISceneNode.h"

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Styles/ConstraintStyle.hpp"
#include "Glue/Model/Graph.hpp"
#include "Glue/Model/Node.hpp"
#include "Glue/Model/Link.hpp"
#include "Glue/Model/Structure.hpp"

#include "ISceneNode.h"

#include "Glue/Model/Graph.hpp"

#include "Glue/Avatar/AvatarComponent.hpp"
#include "Glue/Bullet/BulletComponent.hpp"
#include "Glue/EditorGUI/EditorGUIComponent.hpp"
#include "Glue/Irrlicht/IrrlichtComponent.hpp"
#include "Glue/Model/TimeComponent.hpp"

#include <vector>
#include <string>
#include <memory>

namespace Glue
{
    class Graph : public IGraph
    {
    private:
        Avatar::IAvatarComponent* avatar_cmp;
        Bullet::IBulletComponent* blt_cmp;
        Irrlicht::IIrrlichtComponent* irr_cmp;
        TimeComponent* time_cmp;

        std::vector<Node*> nodes;

    public:

        Graph(
                Avatar::AvatarComponent* avatar_cmp,
                Bullet::BulletComponent* blt_cmp,
                Irrlicht::IrrlichtComponent* irr_cmp,
                TimeComponent* time_cmp);

        virtual ~Graph();

        virtual Node* addNode(NodeStyle const& style);

        virtual Link* addLink(LinkStyle const& style, Node* fromNode, Node* toNode);

        virtual void removeLink(Link* link) const;

        // Deprecated?  Not sure...
        virtual void playSound(std::string const& file);

        virtual void createCamera(Node* lockObj);

        //void removeConstraint(Constraint *constraint);

        //void addConstraint(ConstraintStyle const &style, Node *objA, Node *objB);

        virtual Node* nodeToGameObj(irr::scene::ISceneNode* node) const;

        virtual void removeObj(Node* obj);

        virtual Structure* addStructure(Structure* structure, Structure* leftHandSide);
    };

}
