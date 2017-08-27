#pragma once

namespace Glue {

    enum class LinkTypes
    {
        none,
        lookAt,
        mouseDrag,
        physConstraint
    };

    struct LinkStyle
    {
        LinkTypes linkType;
        LinkStyle(LinkTypes linkType = LinkTypes::none);
    };

}
