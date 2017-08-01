#pragma once

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
                 MenuPath const& path,
                 AbstractMenu* parent=nullptr);

    virtual void drawBorder(const core::rect<s32>& pos,
            SColor colorLeftUp, SColor colorRightUp,
            SColor colorLeftDown, SColor colorRightDown,
            const core::rect<s32>* clip) = 0;

	virtual void drawText(const std::string& text, const core::rect<s32>& position,
		video::SColor color, bool hcenter, bool vcenter,
		const core::rect<s32>* clip) = 0;

public:
    virtual ~AbstractMenu();
    virtual AbstractMenu* load();
    virtual AbstractMenu* doKey(EKEY_CODE key);
    virtual void draw();
};

}
