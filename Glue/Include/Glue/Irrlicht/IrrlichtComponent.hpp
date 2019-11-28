#pragma once

#include "Glue/Model/Component.hpp"
#include "Glue/Model/Node.hpp"

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

    IrrlichtComponent& setGraph(Graph* value);

    irr::ITimer* get_deviceTimer();

    void addNode(Node* node);
    void playSound(std::string const& file);
    void beforeGraphics();
    void onGraphics(Scalar timeElapsed);
    void afterGraphics();
    bool shouldRun() const;
    Node* nodeToGameObj(irr::scene::ISceneNode*);
    void removeObj(Node* obj);
};

}
