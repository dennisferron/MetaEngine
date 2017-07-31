#pragma once

namespace Glue { namespace Bullet {
    class Mount;
}}

namespace Glue { namespace Bullet {

class ConstraintObj
{
protected:
    LinkStyle* style;
    Mount* objA;
    Mount* objB;

    // Create in derived class
    //constraint ::= nil

public:
    virtual ~ConstraintObj();
};

}}
