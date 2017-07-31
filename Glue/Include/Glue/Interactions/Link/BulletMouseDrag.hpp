#pragma once

namespace Glue { namespace Irrlicht {
    class MouseDragLinkAttribute;
    class NodeAttribute;
}}

namespace Glue { namespace Bullet {
    class Component;
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
    Bullet::Component* bulletComp;
    Node* toNode;

public:

    BulletMouseDrag(
        Irrlicht::MouseDragLinkAttribute* mouseAttr,
        Bullet::Component* bulletComp,
        Node* toNode
    );
    ~BulletMouseDrag();
};

}
