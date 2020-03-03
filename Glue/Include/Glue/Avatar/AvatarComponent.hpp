#pragma once

#include "Glue/Avatar/AvatarInterfaces.hpp"
#include "Glue/Model/ModelInterfaces.hpp"

namespace Glue::Avatar
{

class AvatarComponent : public IAvatarComponent
{
public:
    AvatarComponent();
    ~AvatarComponent();

    void attachControl(INode* node) final;
    void beforePhysics(TimeInfo const&) final;
    NodeAttribute*addNode(INode* node) final;
};

}
