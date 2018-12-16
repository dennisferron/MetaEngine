#pragma once

#include <string>

#include "ISceneNode.h"
#include "ISceneManager.h"
#include "ITexture.h"

#include "Glue/Irrlicht/Assets.hpp"
#include "Glue/Styles/GameObjStyle.hpp"

namespace Glue { namespace Irrlicht {

class SceneNodes
{
private:

    irr::scene::ISceneManager* smgr;
    Assets* assets;

public:

    SceneNodes(irr::scene::ISceneManager* smgr, Assets* assets);

    irr::video::ITexture* loadTexture(GameObjStyle* style, std::string const& key);
    irr::scene::ISceneNode* skybox(GameObjStyle* style);
    irr::scene::ISceneNode* default_(GameObjStyle* style, irr::scene::IMesh* shape);
};

}}
