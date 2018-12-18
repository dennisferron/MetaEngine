#pragma once

#include <memory>

#include "SColor.h"
#include "rect.h"
#include "Keycodes.h"

namespace Glue {

class MainWindow;
class MenuPath;

class AbstractMenu
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

protected:

    AbstractMenu(
                 MainWindow* window,
                 MenuPath* path,
                 AbstractMenu* parent=nullptr);

    virtual void drawBorder(const irr::core::rect<irr::s32>& pos,
            irr::video::SColor colorLeftUp, irr::video::SColor colorRightUp,
							irr::video::SColor colorLeftDown, irr::video::SColor colorRightDown,
            const irr::core::rect<irr::s32>* clip) = 0;

	virtual void drawText(const std::string& text, const irr::core::rect<irr::s32>& position,
		irr::video::SColor color, bool hcenter, bool vcenter,
		const irr::core::rect<irr::s32>* clip) = 0;

public:
    virtual ~AbstractMenu();
    virtual AbstractMenu* load();
    virtual AbstractMenu* doKey(irr::EKEY_CODE key);
    virtual void draw();
};

}
