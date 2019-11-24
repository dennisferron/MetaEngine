#pragma once

namespace Glue { namespace Irrlicht {
    class MouseDragLinkAttribute;
    class IrrlichtAttribute;
}}

namespace Glue { namespace Bullet {
    class BulletComponent;
    class ConstraintAttribute;
}}

namespace Glue {
    class Node;
}

namespace Glue {

class BulletMouseDrag
{
private:
    Irrlicht::MouseDragLinkAttribute* mouseAttr;
    Bullet::BulletComponent* bulletComp;
    Node* toNode;

public:

    BulletMouseDrag(
        Irrlicht::MouseDragLinkAttribute* mouseAttr,
        Bullet::BulletComponent* bulletComp,
        Node* toNode
    );
    ~BulletMouseDrag();
};

}
