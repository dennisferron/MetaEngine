#pragma once

#include <functional>

namespace irr { namespace core {
    class vector2di;
}}

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
    void dragging(Scalar X, Scalar Y, MouseInput const& mouseInput);
    void dragToScreenPos(Scalar X, Scalar Y);
    Node* selectNode(Scalar X, Scalar Y);
};

}}
