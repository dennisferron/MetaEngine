#pragma once

#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Styles/LinkStyle.hpp"

#include <vector>

namespace Glue
{
    class Link : public ILink
    {
    private:
        LinkStyle style;
        INode* fromNode;
        INode* toNode;

        std::vector<LinkAttribute*> attributes;

    public:
        Link(LinkStyle const& style, INode* fromNode, INode* toNode);

        LinkStyle const& get_style() const final;

        INode* get_fromNode() const final;

        INode* get_toNode() const final;

        void addAttribute(LinkAttribute* attr) final;
        std::vector<LinkAttribute*> const& get_attributes() const final;
    };

}
