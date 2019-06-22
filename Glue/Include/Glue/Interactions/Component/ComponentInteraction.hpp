#pragma once

#include "Glue/Interactions/Component/ComponentInteraction.hpp"

#include <vector>

namespace Glue {

class ComponentInteraction
{
    // This list is shared among all Link clones
    static std::vector<ComponentInteraction*> possibleInteractions;

    static void registerInteraction(ComponentInteraction* interaction);
};

}
