#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "btTransform.h"

namespace Glue { namespace Bullet {

class ShapeOffsets
{
public:
    btTransform get_transform(NodeStyle const& style) const;

private:
    btTransform none(NodeStyle const& style) const;
    btTransform ball(NodeStyle const& style) const;
    btTransform box(NodeStyle const& style) const;
    btTransform cyl(NodeStyle const& style) const;
    btTransform cylX(NodeStyle const& style) const;
    btTransform cylZ(NodeStyle const& style) const;
    btTransform cone(NodeStyle const& style) const;
    btTransform coneX(NodeStyle const& style) const;
    btTransform coneZ(NodeStyle const& style) const;
    btTransform hills(NodeStyle const& style) const;
    btTransform mesh(NodeStyle const& style) const;
    btTransform cloth(NodeStyle const& style) const;
};

}}
