#pragma once

#include "IMesh.h"
#include "ISceneNode.h"

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Irrlicht/DisplayShapes.hpp"

namespace Glue { namespace Irrlicht {

class ShapeBuilder
{
private:
    DisplayShapes* displayShapes;

    void changeTextureWrap(irr::scene::IMesh* mesh) const;

public:
    ShapeBuilder(DisplayShapes* displayShapes);
    irr::scene::IMesh* create(GameObjStyle style) const;
};

}}
