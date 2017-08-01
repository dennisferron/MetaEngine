#pragma once

namespace Glue {

class MainWindow
{
public:
    virtual ~MainWindow();
    virtual int windowSizeX() const;
    virtual int windowSizeY() const;
};

}
