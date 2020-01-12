#pragma once

#include "Glue/Styles/ConstraintStyle.hpp"

#include <optional>

namespace Glue
{
    enum class LinkTypes
    {
        none,
        lookAt,
        mouseDrag,
        physConstraint
    };

    class LinkStyle
    {
    public:
        LinkTypes linkType;
        std::optional<ConstraintStyle> constraint;
        LinkStyle(LinkTypes linkType = LinkTypes::none);
        LinkStyle(ConstraintStyle const& constraint);
    };

}
