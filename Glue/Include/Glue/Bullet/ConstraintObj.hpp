#pragma once

namespace Glue {
    class Node;
}

namespace Glue { namespace Bullet {

class ConstraintObj
{
protected:
    LinkStyle* style;
    Node* objA;
    Node* objB;

    // Create in derived class
    //constraint ::= nil

public:
    virtual ~ConstraintObj();
};

}}
