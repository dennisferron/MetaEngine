#include "Glue/Irrlicht/SceneNodeBuilder.hpp"

using namespace irr::scene;
using namespace irr::core;
using namespace irr::video;

namespace Glue { namespace Irrlicht {

SceneNodeBuilder::SceneNodeBuilder(ShapeBuilder* shapeBuilder, Assets* assets, irr::scene::ISceneManager* smgr)
    : shapeBuilder(shapeBuilder), assets(assets), smgr(smgr)
{
}

        irr::video::ITexture* SceneNodeBuilder::loadTexture(GameObjStyle const& style, std::string const& key) const
        {
            throw "Implement conversion from string to texture keys enum, or change signature of this function.";
            //assets->loadTextureFromFile(style.textureMap[key]);
        }

        irr::scene::ISceneNode* SceneNodeBuilder::skybox(GameObjStyle const& style) const
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

        irr::scene::ISceneNode* SceneNodeBuilder::default_sceneNode(GameObjStyle const& style, irr::scene::IMesh* shape)
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

ISceneNode* SceneNodeBuilder::buildSceneNode(GameObjStyle const& style)
{
    ISceneNode* sceneNode = nullptr;

    auto shape = shapeBuilder->create(style);

    if (shape == nullptr)
        sceneNode == nullptr;
    else
        sceneNode = default_sceneNode(style, shape);

    if (sceneNode != nullptr)
    {
        sceneNode->setMaterialFlag(EMF_LIGHTING, true);

        // TODO: Also create material if wire frame
        if (style.textureFile != "")
        {
            auto texture = assets->loadTextureFromFile(style.textureFile);
            sceneNode->setMaterialTexture(0, texture);
            sceneNode->setMaterialType(EMT_SOLID);
            //sceneNode->setMaterialFlag(EMF_LIGHTING, false);
            sceneNode->setMaterialFlag(EMF_LIGHTING, true);

            auto material = sceneNode->getMaterial(0);

            // Does this do any good?
            material.ColorMaterial = 0;

            // TODO:  Add shininess as a style property
            material.Shininess = 50;

            material.SpecularColor = SColor(25, 25, 25, 25);

            // Setting one of these (diffuse maybe?) really takes the depth out of lighting
            // and makes a textured rigid body look dull
            //material set_AmbientColor(SColor tmpWithARGB(255, 255, 255, 255))
            //material set_DiffuseColor(SColor tmpWithARGB(255, 128, 128, 128))
            //material set_EmissiveColor(SColor tmpWithARGB(255, 5, 5, 5))

            // TODO:  Share node creation code among game objects.
            // BUG: won't get called without texture file
            material.Wireframe = style.wireframe;
        }
    }

    return sceneNode;

}

}}
