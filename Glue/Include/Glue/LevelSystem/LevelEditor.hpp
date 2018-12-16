#pragma once

#include "Glue/Model/Graph.hpp"
#include "Glue/LevelSystem/Terrain.hpp"

#include "ISceneNode.h"
#include "IVideoDriver.h"
#include "ISceneCollisionManager.h"
#include "IGUIEnvironment.h"
#include "ICursorControl.h"
#include "IGUIButton.h"
#include "SColor.h"

#include "Glue/EditorGUI/Toolbar.hpp"

#include <string>

//virtual irr::scene::ISceneNode * getSceneNodeAndCollisionPointFromRay
//(core::line3df ray, core::vector3df &outCollisionPoint, core::triangle3df &outTriangle, s32 idBitMask=0, ISceneNode *collisionRootNode=0, bool noDebugObjects=false

namespace Glue { namespace LevelSystem {

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
    EditorGUI::Toolbar* toolBar;

    irr::gui::IGUIButton* inOutButton;
    std::string zEquation;
    irr::gui::IGUISpinBox* radiusKnob;

    irr::core::triangle3df* hitTriangle;
    irr::scene::ISceneNode* selectedSceneNode;
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

}}
