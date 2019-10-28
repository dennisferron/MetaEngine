#pragma once

#include "SColor.h"
#include "ISceneNode.h"

#include "Glue/Irrlicht/ShapeBuilder.hpp"
#include "Glue/Irrlicht/SceneNodes.hpp"
#include "Glue/Irrlicht/Assets.hpp"

namespace Glue { namespace Irrlicht {

class SceneNodeBuilder
{
private:

    ShapeBuilder* shapeBuilder;
    SceneNodes* sceneNodes;
    Assets* assets;

public:

    SceneNodeBuilder(ShapeBuilder* shapeBuilder, SceneNodes* sceneNodes, Assets* assets);
    irr::scene::ISceneNode* buildSceneNode(GameObjStyle style) const;
};

}}
