#pragma once

#include "Finagle/Attribute.hpp"

namespace Fngle {

template <typename T>
class Consequent
{
    template <typename... A>
    Consequent(Attribute<A> const&... attrs)
    {
    }
};

}

/*

The Frame has attributes and consequents.  Consequents follow from
attributes.  Some attributes may also follow from prior consequents.

When all of the attributes needed by a consequent are inhabited, the
Consequent<T> creates an Instance<T> (the interaction object).

The Consequent creates the T instance with actual values for the attributes.
The Instance<T> is really just a wrapper with a virtual delete function.

Setting (or resetting) an Attribute in a Frame returns a new Frame with
that Attribute set (or reset) and with any applicable Consequents (re)set as well.

Attributes which follow from Consequents are determined by the Frame participating
in the Consequent instantiation process when Attributes are set, so that instead
of Frame0 -> Frame1 the process might go Frame0 -> (Frame1 -> Frame2) -> Frame3
where internal instantiations are private.

Attribute = Term
Consequent = Coterm

*/
