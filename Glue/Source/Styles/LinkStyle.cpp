#include "Glue/Styles/LinkStyle.hpp"

namespace Glue
{

    LinkStyle::LinkStyle(LinkTypes linkType) :
            linkType(linkType),
            constraint({})
    {
    }

    LinkStyle::LinkStyle(ConstraintStyle const& constraint) :
            linkType(LinkTypes::physConstraint),
            constraint(constraint)
    {
    }
}
