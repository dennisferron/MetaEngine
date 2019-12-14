#pragma once

#include "SColor.h"
#include "ISceneNode.h"

#include "Glue/Irrlicht/ShapeBuilder.hpp"
#include "Glue/Irrlicht/Assets.hpp"

namespace Glue { namespace Irrlicht {

class SceneNodeBuilder
{
private:

    ShapeBuilder* shapeBuilder;
    Assets* assets;
    irr::scene::ISceneManager* smgr;

    irr::scene::ISceneNode* skybox(GameObjStyle const& style) const;
    irr::video::ITexture* loadTexture(GameObjStyle const& style, std::string const& key) const;
    irr::scene::ISceneNode* default_sceneNode(GameObjStyle const& style, irr::scene::IMesh* shape);

public:

    SceneNodeBuilder(ShapeBuilder* shapeBuilder, Assets* assets, irr::scene::ISceneManager* smgr);
    irr::scene::ISceneNode* buildSceneNode(GameObjStyle const& style);
};

}}
