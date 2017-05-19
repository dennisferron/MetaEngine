#pragma once

#include <string>

namespace Glue {

class UserInterfaceStyle;

class UserInterfaceRepresentation
{
private:
    UserInterfaceStyle style;
    bool isMouseDraggable;

public:
    UserInterfaceRepresentation(UserInterfaceStyle const& style);
};

}
