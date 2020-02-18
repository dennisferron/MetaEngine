#pragma once

#include <memory>

namespace Glue::EditorGUI
{

class EditorGUIComponent
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    EditorGUIComponent();
    ~EditorGUIComponent();
};

}
