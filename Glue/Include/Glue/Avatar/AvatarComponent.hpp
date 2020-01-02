#pragma once

#include "Glue/Model/Component.hpp"
#include "Glue/Model/Node.hpp"
#include "Glue/Model/TimeComponent.hpp"

#include <memory>

namespace Glue { namespace Avatar {

class AvatarComponent : public Component
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    AvatarComponent();
    ~AvatarComponent();

    void attachControl(Node* node);
    void beforePhysics(TimeInfo const&);
};

}}
