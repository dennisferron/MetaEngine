#pragma once

#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/Model/TimeComponent.hpp"

#include <memory>

namespace Glue::Avatar
{

class AvatarComponent
{
public:
    AvatarComponent();
    ~AvatarComponent();

    void attachControl(INode* node);
    void beforePhysics(TimeInfo const&);
};

}
