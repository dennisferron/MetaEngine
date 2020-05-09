#pragma once

#include "Glue/Model/Link.hpp"
#include "Glue/Styles/LinkStyle.hpp"

namespace Glue
{
    class LinkFactory
    {
    public:
        Link* create(LinkStyle const& style, Node* nodeA, Node* nodeB) const;
    };
}