#pragma once

#include <memory>

namespace Glue {
    class Event;
    class GuiElement;
}

namespace Glue { namespace Irrlicht {

class GuiEvents
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    GuiEvents();
    ~GuiEvents();

    GuiEvents& handle(Event* event);
    void register_(GuiElement* guiEl);
};

}}
