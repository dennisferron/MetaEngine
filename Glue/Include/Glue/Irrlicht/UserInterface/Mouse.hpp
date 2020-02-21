#pragma once

#include "vector2d.h"

#include "Glue/LevelSystem/Tile.hpp"

#include <functional>
#include <memory>

namespace irr { namespace video {
    class ITriangle;
}}

namespace Glue { namespace Irrlicht {

class Event;

class Mouse
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    Mouse();
    ~Mouse();

    bool handle(Event* event);
    void drawCursor();
    void highlightTile(irr::core::vector2di const& mousePos);
    Tile* getTile(irr::core::vector2di const& mousePos) const;
    irr::video::ITriangle* selectTriangle(Scalar X, Scalar Y);
    void handleMouse(Scalar X, Scalar Y, int button);
    irr::core::vector3df getPlaneIntersection(Scalar X, Scalar Y) const;
    void dragging(Scalar X, Scalar Y, irr::SEvent::SMouseInput const& mouseInput);
    void dragToScreenPos(Scalar X, Scalar Y);
    INode* selectNode(Scalar X, Scalar Y);
};

}}
