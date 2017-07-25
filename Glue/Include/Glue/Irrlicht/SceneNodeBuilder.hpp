#pragma once

namespace irr { namespace video {
    class SColor;
}}

namespace irr { namespace scene {
    class ISceneNode;
}}

namespace Glue {

class ShapeBuilder;
class SceneNodes;
class Assets;

class SceneNodeBuilder
{
private:

    ShapeBuilder* shapeBuilder;
    SceneNodes* sceneNodes;
    Assets* assets;

public:

    SceneNodeBuilder(ShapeBuilder* shapeBuilder, SceneNodes* sceneNodes, Assets* assets);
    ISceneNode* buildSceneNode(GameObjStyle* style) const;
};

}
