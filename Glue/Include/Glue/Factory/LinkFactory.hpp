#pragma once

namespace Glue
{
    class LinkFactory
    {
    public:
        Link* create(LinkStyle const& style, Node* nodeA, Node* nodeB) const;
    };
}