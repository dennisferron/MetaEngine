#pragma once

#include "Graph.hpp"
#include "Terrain.hpp"

#include <string>

virtual ISceneNode * getSceneNodeAndCollisionPointFromRay
(core::line3df ray, core::vector3df &outCollisionPoint, core::triangle3df &outTriangle, s32 idBitMask=0, ISceneNode *collisionRootNode=0, bool noDebugObjects=false

namespace irr { namespace video {
    class IVideoDriver;
}}

namespace irr { namespace scene {
    class ISceneCollisionManager;
}}

namespace irr { namespace gui {
    class IGUIEnvironment;
    class ICursorControl;
    class IGUIButton;
}}

namespace Glue {

using SColor = irr::video::SColor;
using EKEY_CODE = irr::EKEY_CODE;

class LevelEditor
{
private:
    Graph* engine;
    irr::video::IVideoDriver* driver;
    irr::gui::IGUIEnvironment* gui;
    irr::gui::ICursorControl* cursor;
    Terrain* terrain;
    irr::scene::ISceneCollisionManager* collMan;
    Toolbar* toolBar;

    irr::gui::IGUIButton* inOutButton;
    std::string zEquation;
    irr::gui::IGUISpinBox* radiusKnob;

    irr::core::triangle3df* hitTriangle;
    ISceneNode* selectedSceneNode;
    irr::core::vector3df* collisionPoint;

public:

    LevelEditor(Graph* engine);
    irr::video::ITexture* loadTexture(std::string const& fileName);
    void drawCursor();
    void highlightTile(irr::core::vector2di const& mousePos);
    Tile* getTile(irr::core::vector2di const& mousePos);
    irr::core::triangle3df const& selectTriangle(int X, int Y);
    void handleMouse(int X, int Y, int button);
    void selectNode(int X, int Y);
};

}
