#pragma once

#include <string>

namespace irr { namespace scene {
    class ISceneManager;
}}

namespace irr { namespace video {
    class ITexture;
}}

namespace Glue {

class Assets;
class GameObjStyle;

class SceneNodes
{
private:

    irr::scene::ISceneManager* smgr;
    Assets* assets;

    irr::video::ITexture* loadTexture(GameObjStyle* style, std::string const& key);
    irr::scene::ISceneNode* skybox(GameObjStyle* style);
    irr::scene::ISceneNode* default_(GameObjStyle* style, irr::scene::IMesh* shape);
};

}
