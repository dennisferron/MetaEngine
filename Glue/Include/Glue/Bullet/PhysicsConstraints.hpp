#pragma once

class btRigidBody;

namespace Glue {
    class LinkStyle;
}

namespace Glue { namespace Bullet {

    namespace PhysicsConstraints {

        void none();
        btPoint2PointConstraint mouseDrag(LinkStyle* style, btRigidBody& rbA, btRigidBody& rbB);
        btSliderConstraint slider(LinkStyle* style, btRigidBody& rbA, btRigidBody& rbB);
        btConeTwistConstraint coneTwist(LinkStyle* style, btRigidBody& rbA, btRigidBody& rbB);
        btHingeConstraint hinge(LinkStyle* style, btRigidBody& rbA, btRigidBody& rbB);
        GearConstraint gear(LinkStyle* style, btRigidBody& rbA, btRigidBody& rbB);
        btPoint2PointConstraint point2point(LinkStyle* style, btRigidBody& rbA, btRigidBody& rbB);
        btGeneric6DofConstraint generic(LinkStyle* style, btRigidBody& rbA, btRigidBody& rbB);
        btGeneric6DofSpringConstraint genericSpring(LinkStyle* style, btRigidBody& rbA, btRigidBody& rbB);

    }
}}
