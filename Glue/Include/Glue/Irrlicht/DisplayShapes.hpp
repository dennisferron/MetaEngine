#pragma once

#include "IMesh.h"
#include "IGeometryCreator.h"

#include "Glue/Styles/GameObjStyle.hpp"

namespace Glue { namespace Irrlicht {

class DisplayShapes
{
public:
    DisplayShapes(irr::scene::IGeometryCreator* geometry);
    irr::scene::IMesh* create(GameObjStyle const& style) const;

private:

    irr::scene::IGeometryCreator* geometry;

    irr::scene::IMesh* none(GameObjStyle const& style) const;
    irr::scene::IMesh* ball(GameObjStyle const& style) const;
    irr::scene::IMesh* box(GameObjStyle const& style) const;
    irr::scene::IMesh* cyl(GameObjStyle const& style) const;
    irr::scene::IMesh* cylX(GameObjStyle const& style) const;
    irr::scene::IMesh* cylZ(GameObjStyle const& style) const;
    irr::scene::IMesh* cone(GameObjStyle const& style) const;
    irr::scene::IMesh* coneX(GameObjStyle const& style) const;
    irr::scene::IMesh* coneZ(GameObjStyle const& style) const;
    irr::scene::IMesh* hills(GameObjStyle const& style) const;
    irr::scene::IMesh* plane(GameObjStyle const& style) const;
    irr::scene::IMesh* cloth(GameObjStyle const& style) const;
    irr::scene::IMesh* mesh(GameObjStyle const& style) const;
};

}}
