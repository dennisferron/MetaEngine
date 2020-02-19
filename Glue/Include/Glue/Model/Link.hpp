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

        std::vector<LinkAttribute> attributes;

    public:
        Link(LinkStyle const& style, INode* fromNode, INode* toNode);

        void addAttribute(LinkAttribute attr) override;
    };

}
