#pragma once

#include "IMesh.h"
#include "IGeometryCreator.h"

#include "Glue/Styles/GameObjStyle.hpp"

namespace Glue::Irrlicht
{
    irr::scene::IMesh* create_display_shape(GameObjStyle const &style, irr::scene::IGeometryCreator* geometry);
}
