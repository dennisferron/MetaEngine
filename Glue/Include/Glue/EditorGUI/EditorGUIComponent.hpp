#pragma once

#include <memory>

namespace Glue { namespace EditorGUI {

class EditorGUIComponent
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    EditorGUIComponent();
    ~EditorGUIComponent();
};

}}
