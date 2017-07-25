namespace irr { namespace scene {
    class ISceneNode;
    class IMesh;
}}

namespace Glue {

class DisplayShapes;
class GameObjStyle;

class ShapeBuilder
{
private:
    DisplayShapes* displayShapes;

    void changeTextureWrap(irr::scene::IMesh* mesh) const;

public:
    ShapeBuilder(DisplayShapes* displayShapes);
    irr::scene::ISceneNode* create(GameObjStyle* style) const;
};

}
