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
        std::vector<Shape*> shapes;
        std::vector<Node*> nodes;
        std::vector<Link*> links;

    public:

        Graph();

        ~Graph();

        void addComponent(IGraphObserver* component);

        std::vector<IGraphObserver*> const& get_attributes() const
        { return components; }

        void addShape(Shape* shape);

        void addNode(Node* node);

        void addLink(Link* link);

        // Deprecated?  Not sure...
        //void playSound(std::string const& file);

        //void createCamera(Node* lockObj);

        //Node* nodeToGameObj(irr::scene::ISceneNode* node) const;

        //Structure* addStructure(Structure* structure, Structure* leftHandSide);
    };

}
