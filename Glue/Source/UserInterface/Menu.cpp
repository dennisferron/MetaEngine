
#include "Glue/UserInterface/Menu.hpp"
#include "Glue/Model/Graph.hpp"
#include "irrlicht.h"

#include <functional>
#include <vector>

#include "Glue/UserInterface/MainWindow.hpp"

namespace Glue {

using MenuItem = std::function<void()>;

using SColor = irr::video::SColor;
using EKEY_CODE = irr::EKEY_CODE;

class AbstractMenu::Impl
{
private:

    AbstractMenu* self;
    Graph* graph;
    MainWindow* window;
    MenuPath* path;
    AbstractMenu* parent;
    std::vector<AbstractMenu*> items;
    int lineH = 50;
    int selectedLine = 0;
    SColor selectedColor = SColor(255, 255, 255, 255);
    SColor regularColor = SColor(120, 120, 120, 120);

public:

    Impl(AbstractMenu* self, Graph* graph, MenuPath* path, AbstractMenu* parent=nullptr);
    void load();
    AbstractMenu* doKey(EKEY_CODE key);
    void draw();
};

AbstractMenu::~AbstractMenu()
{
}

AbstractMenu* AbstractMenu::load()
{
    impl->load();
    return this;
}

AbstractMenu* AbstractMenu::doKey(EKEY_CODE key)
{
    return doKey(key);
}

void AbstractMenu::draw()
{
    impl->draw();
}

AbstractMenu::Impl::Impl(AbstractMenu* self, Graph* graph, MenuPath* path, AbstractMenu* parent)
    : self(self), graph(graph), path(path), parent(parent)
{
    load();
}

void AbstractMenu::Impl::load()
{
    // TODO: Load menu from database.

    selectedLine = 0;
}

AbstractMenu* AbstractMenu::Impl::doKey(EKEY_CODE key)
{
    if (items.size() == 0)
        return parent;

    switch (key)
    {
        case irr::KEY_ESCAPE:
    case irr::KEY_BACK:
        if (parent != nullptr)
            return parent->load();
    case irr::KEY_DOWN:
        ++selectedLine;
        if (selectedLine >= items.size())
            selectedLine = 0;
        return self;
    case irr::KEY_UP:
        --selectedLine;
        if (selectedLine < 0)
            selectedLine = items.size() - 1;
        return self;
    case irr::KEY_RETURN:
        // TODO:  Execute menu item at selected line.
        default:
        return self;
    };
}

void AbstractMenu::Impl::draw()
{
    Scalar borderX = window->windowSizeX() / 5;
    Scalar borderY = window->windowSizeY() / 5;

    Scalar top = borderY;
    Scalar bottom = window->windowSizeY() - borderY;
    Scalar left = borderX;
    Scalar right = window->windowSizeX() - borderX;

    irr::core::recti pos(left, top, right, bottom);

    SColor colorLeftUp(200, 30, 60, 30);
    SColor colorRightUp(200, 30, 90, 60);
    SColor colorLeftDown(200, 50, 50, 90);
    SColor colorRightDown(200, 60, 30, 90);

    const irr::core::rect< irr::s32 >* clip = nullptr;

    self->drawBorder(
        pos,
        colorLeftUp,
        colorRightUp,
        colorLeftDown,
        colorRightDown,
        clip
    );

    Scalar lineY = (window->windowSizeY() - lineH * items.size()) / 2;
    for (int i=0; i<items.size(); ++i)
    {
        auto item = items[i];
        std::string str = "TODO: Get name string from menu path";
        irr::core::recti position(0, lineY, window->windowSizeX(), lineY + lineH);
        SColor color = (i == selectedLine) ? selectedColor : regularColor;
        bool hcenter = true;
        bool vcenter = true;

        self->drawText(
            str,
            position,
            color,
            hcenter,
            vcenter,
            clip
        );
        lineY += lineH;
    }
}

}
