#include "Glue/Bullet/ShapeBuilder.hpp"
#include "Glue/Bullet/ShapeOffsets.hpp"
#include "Glue/Bullet/PhysicsShapes.hpp"

#include "btRigidBody.h"

namespace Glue::Bullet
{

btCollisionShape* ShapeBuilder::create(NodeStyle const& style, irr::scene::IMesh* dispShapeMesh) const
{
    auto physShape = create_physics_shape(style, dispShapeMesh);

    if (physShape != nullptr && style.margin)
        physShape->setMargin(*style.margin);

    return physShape;
}

btTransform ShapeBuilder::getOffset(NodeStyle const& style) const
{
    return get_shape_transform(style);
}

}