#pragma once

#include <functional>

namespace irr {
    enum EKEY_CODE;
}

namespace Glue {

using MenuItem = std::function<void()>;

class Menu : public AbstractMenu
{
private:

    class Impl;
    std::unique_ptr<Impl> impl;

public:

    MenuItem(Graph* engine, MenuPath* path, Menu* parent);
    void load();
    Menu& doKey(irr::EKEY_CODE key);
    void draw();
};

}
