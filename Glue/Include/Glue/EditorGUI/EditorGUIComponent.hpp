#pragma once

#include "Glue/Model/Component.hpp"

#include <memory>

namespace Glue { namespace EditorGUI {

class EditorGUIComponent : public Component
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    EditorGUIComponent();
    ~EditorGUIComponent();
};

}}
