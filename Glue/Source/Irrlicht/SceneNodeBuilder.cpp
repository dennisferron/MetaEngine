#include "Glue/Irrlicht/SceneNodeBuilder.hpp"

using namespace irr::scene;

namespace Glue { namespace Irrlicht {

SceneNodeBuilder::SceneNodeBuilder(ShapeBuilder* shapeBuilder, SceneNodes* sceneNodes, Assets* assets)
    : shapeBuilder(shapeBuilder), sceneNodes(sceneNodes), assets(assets)
{
}

ISceneNode* SceneNodeBuilder::buildSceneNode(GameObjStyle* style) const
{
    throw "Find replacement for hasSlot and perform on sceneNodes";

//    ISceneNode* sceneNode = nullptr;
//
//    if (style->dispShape == ObjShapes::none)
//    {
//        sceneNode = nullptr;
//    }
//    else if (sceneNodes->hasSlot(style->dispShape) )
//    {
//        sceneNode = sceneNodes->perform(style->dispShape, style);
//    }
//    else
//    {
//        auto shape = shapeBuilder->create(style);
//        sceneNode = sceneNodes->default_(style, shape);
//    }
//
//    if (sceneNode != nullptr)
//    {
//        sceneNode->setMaterialFlag(EMF_LIGHTING, true);
//
//        // TODO: Also create material if wire frame
//        if (style->texture != nil)
//        {
//            auto texture = assets->loadTextureFromFile(style->texture);
//            sceneNode->setMaterialTexture(0, texture);
//            sceneNode->setMaterialType(EMT_SOLID);
//            //sceneNode->setMaterialFlag(EMF_LIGHTING, false);
//            sceneNode->setMaterialFlag(EMF_LIGHTING, true);
//
//            auto material = sceneNode->getMaterial(0);
//
//            // Does this do any good?
//            material->ColorMaterial = 0;
//
//            // TODO:  Add shininess as a style property
//            material->Shininess = 50;
//
//            material->SpecularColor = SColor(25, 25, 25, 25);
//
//            // Setting one of these (diffuse maybe?) really takes the depth out of lighting
//            // and makes a textured rigid body look dull
//            //material set_AmbientColor(SColor tmpWithARGB(255, 255, 255, 255))
//            //material set_DiffuseColor(SColor tmpWithARGB(255, 128, 128, 128))
//            //material set_EmissiveColor(SColor tmpWithARGB(255, 5, 5, 5))
//
//            // TODO:  Share node creation code among game objects.
//            // BUG: won't get called without texture file
//            material->Wireframe = style->wireframe;
//        }
//    }
//
//    return sceneNode;

}

}}
