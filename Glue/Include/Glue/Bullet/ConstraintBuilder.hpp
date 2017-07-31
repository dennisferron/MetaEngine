#pragma once

class btTransform;
class btRigidBody;

namespace Glue { namespace Bullet {
    class ConstraintObj;
}}

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
