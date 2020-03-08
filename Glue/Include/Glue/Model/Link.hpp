#pragma once

#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Styles/LinkStyle.hpp"

#include <vector>

namespace Glue
{
    class Link
    {
    private:
        LinkStyle style;
        Node* fromNode;
        Node* toNode;

        std::vector<LinkAttribute*> attributes;

    public:
        Link(LinkStyle const& style, Node* fromNode, Node* toNode);

        LinkStyle const& get_style() const;

        Node* get_fromNode() const;

        Node* get_toNode() const;

        void addAttribute(LinkAttribute* attr);
        std::vector<LinkAttribute*> const& get_attributes() const;
    };

}
