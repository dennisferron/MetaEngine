#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Animators/MotionStateAnimator.hpp"

#include <vector>
#include <Glue/Avatar/AvatarComponent.hpp>
#include <Glue/Avatar/AvatarAttribute.hpp>
#include <Glue/Avatar/Camera.hpp>

#include <memory>

namespace Glue
{
    class NodeInteractions
    {

    };

class Node : public INode
{
private:
    NodeStyle style;
    NodeInteractions interactions;
    std::vector<NodeAttribute> attributes;

public:

    Node(NodeStyle const& style);
    ~Node();

    NodeStyle const& get_style() const override;
    void addAttribute(NodeAttribute attr) override;
};

}
