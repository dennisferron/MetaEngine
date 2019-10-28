#pragma once

#include "IMesh.h"
#include "IGeometryCreator.h"

#include "Glue/Styles/GameObjStyle.hpp"

namespace Glue { namespace Irrlicht {

class DisplayShapes
{
private:

    irr::scene::IGeometryCreator* geometry;

public:
    DisplayShapes(irr::scene::IGeometryCreator* geometry);

    irr::scene::IMesh* none(GameObjStyle style) const;
    irr::scene::IMesh* ball(GameObjStyle style) const;
    irr::scene::IMesh* box(GameObjStyle style) const;
    irr::scene::IMesh* cyl(GameObjStyle style) const;
    irr::scene::IMesh* cylX(GameObjStyle style) const;
    irr::scene::IMesh* cylZ(GameObjStyle style) const;
    irr::scene::IMesh* cone(GameObjStyle style) const;
    irr::scene::IMesh* coneX(GameObjStyle style) const;
    irr::scene::IMesh* coneZ(GameObjStyle style) const;
    irr::scene::IMesh* hills(GameObjStyle style) const;
    irr::scene::IMesh* plane(GameObjStyle style) const;
    irr::scene::IMesh* cloth(GameObjStyle style) const;
    irr::scene::IMesh* mesh(GameObjStyle style) const;
    irr::scene::IMesh* skybox(GameObjStyle style) const;
};

}}
