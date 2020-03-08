#pragma once

#include "Glue/Avatar/AvatarInterfaces.hpp"

namespace Glue::Avatar
{

class AvatarComponent : public IAvatarComponent
{
public:
    AvatarComponent();
    ~AvatarComponent();

    void attachControl(Node* node) final;
    void beforePhysics(TimeInfo const&) final;
    NodeAttribute*addNode(Node* node) final;
};

}
