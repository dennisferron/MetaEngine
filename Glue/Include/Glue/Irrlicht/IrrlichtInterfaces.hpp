#pragma once

#include "Glue/Irrlicht/UserInterface/UserInterface.hpp"

#include "Camera.hpp"

#include "Assets.hpp"

#include "DisplayShapes.hpp"
#include "ShapeBuilder.hpp"
#include "SceneNodeBuilder.hpp"

#include "IrrlichtComponent.hpp"

#include "IrrlichtAttribute.hpp"

#pragma once

#include "Glue/Model/Node.hpp"

#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"

#include "ITimer.h"
#include "ISceneNode.h"


#include <string>

namespace Glue
{
    class INode;
}

namespace Glue::Irrlicht
{
    class IIrrlichtComponent
    {
    public:

        virtual ~IrrlichtComponent() {}

        irr::ITimer* get_deviceTimer();

        IrrlichtAttribute* addNode(Glue::Node* node);
        void playSound(std::string const& file);
        void beforeGraphics();
        void onGraphics(Scalar timeElapsed);
        void afterGraphics();
        bool shouldRun() const;
        INode* nodeToGameObj(irr::scene::ISceneNode*);
        void removeObj(Node* obj);
        void setGraph(Graph* graph);
    };

}
