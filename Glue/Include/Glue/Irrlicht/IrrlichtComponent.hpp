#pragma once

#include "Glue/Model/Graph.hpp"
#include "Glue/Model/Node.hpp"

#include <memory>
#include <string>

namespace irr::scene {
    class ISceneNode;
}

namespace Glue::Irrlicht {

class IrrlichtComponent
{
private:
    struct Impl;
    std::unique_ptr<Impl> impl;

public:

    IrrlichtComponent();
    ~IrrlichtComponent();

    IrrlichtComponent& setGraph(Graph* value);

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
