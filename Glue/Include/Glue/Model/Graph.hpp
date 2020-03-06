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
    class Graph : public IGraph
    {
    private:
        std::vector<IGraphObserver*> components;
        std::vector<INode*> nodes;

    public:

        Graph();

        ~Graph() final;

        void addComponent(IGraphObserver* component) final;

        std::vector<IGraphObserver*> const& get_attributes() const final
        { return components; }

        IShape* addShape(ShapeStyle const& style) final;

        INode* addNode(NodeStyle const& style, IShape* shape) final;

        ILink* addLink(LinkStyle const& style, INode* fromNode, INode* toNode) final;

        void removeLink(ILink* link) const final;

        // Deprecated?  Not sure...
        void playSound(std::string const& file) final;

        void createCamera(INode* lockObj) final;

        //void removeConstraint(Constraint *constraint);

        //void addConstraint(ConstraintStyle const &style, Node *objA, Node *objB);

        INode* nodeToGameObj(irr::scene::ISceneNode* node) const final;

        void removeObj(INode* obj) final;

        IStructure* addStructure(IStructure* structure, IStructure* leftHandSide) final;
    };

}
