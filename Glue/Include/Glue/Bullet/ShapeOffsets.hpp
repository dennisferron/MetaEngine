#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "btTransform.h"

namespace Glue { namespace Bullet {

class ShapeOffsets
{
public:
    btTransform none(NodeStyle const& style);
    btTransform ball(NodeStyle const& style);
    btTransform box(NodeStyle const& style);
    btTransform cyl(NodeStyle const& style);
    btTransform cylX(NodeStyle const& style);
    btTransform cylZ(NodeStyle const& style);
    btTransform cone(NodeStyle const& style);
    btTransform coneX(NodeStyle const& style);
    btTransform coneZ(NodeStyle const& style);
    btTransform hills(NodeStyle const& style);
    btTransform mesh(NodeStyle const& style);
    btTransform cloth(NodeStyle const& style);
};

}}
