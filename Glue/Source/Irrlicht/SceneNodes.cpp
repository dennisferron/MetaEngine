#include "Glue/Irrlicht/SceneNodes.hpp"

using namespace irr::core;

namespace Glue { namespace Irrlicht {

    SceneNodes::SceneNodes(irr::scene::ISceneManager* smgr, Assets* assets)
        : smgr(smgr), assets(assets)
    {
    }

    irr::video::ITexture* SceneNodes::loadTexture(GameObjStyle style, std::string const& key)
    {
        throw "Implement conversion from string to texture keys enum, or change signature of this function.";
        //assets->loadTextureFromFile(style.textureMap[key]);
    }

    irr::scene::ISceneNode* SceneNodes::skybox(GameObjStyle style)
    {
        return smgr->addSkyBoxSceneNode(
                loadTexture(style, "up"),
                loadTexture(style, "down"),
                loadTexture(style, "left"),
                loadTexture(style, "right"),
                loadTexture(style, "front"),
                loadTexture(style, "back"),
                nullptr,    // parent
                0       // id
        );
    }

    irr::scene::ISceneNode* SceneNodes::default_(GameObjStyle style, irr::scene::IMesh* shape)
    {

      return smgr->addMeshSceneNode(
              shape,  // mesh
              nullptr, // parent
              0,         // id
              vector3df(style.x, style.y, -style.z),    // position
              vector3df(0, 0, 0),    // rotation
              vector3df(style.dispScaleX, style.dispScaleY, style.dispScaleZ), // scale
              false  // alsoAddIfMeshPointerZero
        );
    }

    // Debugging - this creates the boxes and arrows
    /*
    sceneNode addChild(
        irr custom OrientationHelperSceneNode new(
            1.0, // size
            sceneNode, // parent
            smgr, // mgr
            0     // id
        )
    )
    */
}}
