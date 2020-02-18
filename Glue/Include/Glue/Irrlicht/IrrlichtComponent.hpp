#pragma once

#include "Glue/Model/Node.hpp"

#include "Glue/Irrlicht/IrrlichtAttribute.hpp"

#include "ITimer.h"
#include "ISceneNode.h"

#include <memory>
#include <string>

namespace Glue::Irrlicht {

class IrrlichtComponent : public Component
{
private:
    struct Impl;
    std::unique_ptr<Impl> impl;

public:

    IrrlichtComponent();
    ~IrrlichtComponent();

    irr::ITimer* get_deviceTimer();

    IrrlichtAttribute* addNode(Glue::Node* node);
    void playSound(std::string const& file);
    void beforeGraphics();
    void onGraphics(Scalar timeElapsed);
    void afterGraphics();
    bool shouldRun() const;
    Node* nodeToGameObj(irr::scene::ISceneNode*);
    void removeObj(Node* obj);
    void setGraph(Graph* graph);
};

}
