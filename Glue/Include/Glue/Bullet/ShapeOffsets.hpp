#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "btTransform.h"

namespace Glue::Bullet
{
    btTransform get_shape_transform(NodeStyle const &style);
}
