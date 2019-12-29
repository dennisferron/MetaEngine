#pragma once

#include "IMesh.h"
#include "ISceneNode.h"

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Irrlicht/DisplayShapes.hpp"

namespace Glue::Irrlicht {

    class ShapeBuilder
    {
    private:
        irr::scene::IGeometryCreator* geometry;

        void changeTextureWrap(irr::scene::IMesh *mesh) const;

    public:
        ShapeBuilder(irr::scene::IGeometryCreator* geometry);

        irr::scene::IMesh *create(GameObjStyle const& style) const;
    };

}
