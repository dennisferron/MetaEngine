#pragma once

#include "irrlicht.h"

#include <functional>

#include "Graph.hpp"

namespace Glue {

using MenuItem = std::function<void()>;

using SColor = irr::video::SColor;
using EKEY_CODE = irr::EKEY_CODE;

class AbstractMenu
{
private:

    Graph* graph;
    std::string path;
    AbstractMenu* parent;
    std::vector<AbstractMenu*> items;
    int lineH = 50;
    int selectedLine = 0;
    SColor selectedColor = SColor(255, 255, 255, 255);
    SColor regularColor = SColor(120, 120, 120, 120);

protected:

    AbstractMenu(Graph* engine, std::string path, AbstractMenu* parent=nullptr)
        : graph(engine), path(path), parent(parent)
    {
        load();
    }

public:

    virtual void load();
    virtual AbstractMenu* doKey(EKEY_CODE key);
    virtual void draw();
    static std::string trimItem(std::string const& item);
};

}
