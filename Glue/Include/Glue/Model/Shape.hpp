#pragma once

#include "btBulletCollisionCommon.h"
#include "SColor.h"
#include "IMesh.h"
#include "ITexture.h"

namespace Glue
{
    struct Shape
    {
        btCollisionShape* physShape;
        irr::scene::IMesh* dispShape;
        btTransform offset;
    };
}
