#pragma once

#include "Glue/Avatar/AvatarInterfaces.hpp"

#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Model/TimeComponent.hpp"

namespace Glue::Avatar
{

class AvatarComponent : public IAvatarComponent
{
public:
    AvatarComponent();
    ~AvatarComponent();

    void attachControl(INode* node);
    void beforePhysics(TimeInfo const&);
};

}
