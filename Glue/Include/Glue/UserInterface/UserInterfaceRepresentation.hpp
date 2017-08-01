// TODO: Figure out what UserInterfaceStyle is.
#pragma once

#include <memory>

namespace Glue {

class UserInterfaceStyle;

class UserInterfaceRepresentation
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:
    UserInterfaceRepresentation(UserInterfaceStyle const& style);
    void setStyle(UserInterfaceStyle const& value);
    void setIsMouseDraggable(bool value);

};

}
