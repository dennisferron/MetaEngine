#pragma once

#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Bullet/BulletInterfaces.hpp"

class btTransform;
class btRigidBody;

namespace Glue::Bullet
{

class ConstraintBuilder : public IConstraintBuilder
{
public:
    ConstraintBuilder();

    IConstraintObj* create(ConstraintStyle const& style, btRigidBody* objA, btRigidBody* objB) override;
};

}
