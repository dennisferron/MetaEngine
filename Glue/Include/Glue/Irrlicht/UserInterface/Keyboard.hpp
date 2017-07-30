#pragma once

namespace Glue {
    class Event;
}

namespace Glue { namespace Irrlicht {

class Keyboard
{
public:
    void handle(Event* event);
};

}}
