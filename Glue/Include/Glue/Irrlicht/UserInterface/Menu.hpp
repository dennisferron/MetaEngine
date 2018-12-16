#pragma once

#include "Glue/Model/Graph.hpp"

#include <functional>

namespace irr {
    enum EKEY_CODE;
}

namespace Glue { namespace Irrlicht {

using MenuItem = std::function<void()>;
class MenuPath;

class Menu
{
private:

    class Impl;
    std::unique_ptr<Impl> impl;

public:

    Menu(Graph* engine, MenuPath* path, Menu* parent);
    void load();
    Menu& doKey(irr::EKEY_CODE key);
    void draw();
};

}}
