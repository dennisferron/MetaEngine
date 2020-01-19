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
#include "Glue/Model/TimeComponent.hpp"

#include <vector>
#include <string>
#include <memory>

namespace Glue
{
    class Graph
    {
    public:

        virtual ~Graph() = 0;
        virtual Node* addNode(NodeStyle const& style) = 0;
        virtual Link* addLink(LinkStyle const& style, Node* fromNode, Node* toNode) = 0;
        virtual void removeLink(Link* link) const = 0;
        virtual void playSound(std::string const& file) = 0;
        virtual void createCamera(Node* lockObj) = 0;
        virtual Node* nodeToGameObj(irr::scene::ISceneNode* node) const = 0;
        virtual void removeObj(Node* obj) = 0;
        virtual Structure* addStructure(Structure* structure, Structure* leftHandSide) = 0;
    };

}
