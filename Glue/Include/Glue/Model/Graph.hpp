#pragma once

#include "ISceneNode.h"

#include "Glue/Avatar/AvatarInterfaces.hpp"
#include "Glue/Bullet/BulletInterfaces.hpp"
#include "Glue/EditorGUI/EditorGUIComponent.hpp"
#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"

#include "Glue/Model/ModelInterfaces.hpp"

#include <vector>
#include <string>
#include <memory>

namespace Glue
{
    class Graph
    {
    private:
        std::vector<IGraphObserver*> components;
        std::vector<Node*> nodes;

    public:

        Graph();

        ~Graph();

        void addComponent(IGraphObserver* component);

        std::vector<IGraphObserver*> const& get_attributes() const
        { return components; }

        Shape* addShape(ShapeStyle const& style);

        Node* addNode(NodeStyle const& style, Shape* shape);

        Link* addLink(LinkStyle const& style, Node* fromNode, Node* toNode);

        void removeLink(Link* link) const;

        // Deprecated?  Not sure...
        void playSound(std::string const& file);

        void createCamera(Node* lockObj);

        //void removeConstraint(Constraint *constraint);

        //void addConstraint(ConstraintStyle const &style, Node *objA, Node *objB);

        Node* nodeToGameObj(irr::scene::ISceneNode* node) const;

        void removeObj(Node* obj);

        Structure* addStructure(Structure* structure, Structure* leftHandSide);
    };

}
