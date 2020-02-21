#pragma once

#include "IMesh.h"
#include "ISceneNode.h"

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Irrlicht/DisplayShapes.hpp"
#include "IrrlichtInterfaces.hpp"

namespace Glue::Irrlicht
{
    class ShapeBuilder : public IShapeBuilder
    {
    private:
        irr::scene::IGeometryCreator* geometry;

        void changeTextureWrap(irr::scene::IMesh* mesh) const;

    public:
        ShapeBuilder(irr::scene::IGeometryCreator* geometry);

        irr::scene::IMesh* create(GameObjStyle const& style) const;
    };
}
