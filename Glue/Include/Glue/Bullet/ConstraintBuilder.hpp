#pragma once

#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Bullet/ConstraintObj.hpp"

class btTransform;
class btRigidBody;

namespace Glue { namespace Bullet {

class ConstraintBuilder
{
public:
    ConstraintBuilder();

    ConstraintObj* create(LinkStyle* style, btRigidBody& objA, btRigidBody& objB);

    // Utility method
    static btTransform getFrame(Mount const& mount);
};

}}
