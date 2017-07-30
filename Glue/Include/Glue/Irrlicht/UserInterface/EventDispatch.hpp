#pragma once

#include <memory>

namespace Glue {
    class EventCode;
    class EventHandler;
}

namespace Glue { namespace Irrlicht {

class EventDispatch
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    EventDispatch();
    void addHandler(EventCode const& enum_, EventHandler* handler);
};

}}
