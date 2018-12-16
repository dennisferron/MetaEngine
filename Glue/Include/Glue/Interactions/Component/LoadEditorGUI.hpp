#pragma once

#include "Glue/Irrlicht/Component.hpp"
#include "Glue/EditorGUI/Component.hpp"
#include "Glue/Avatar/Component.hpp"

namespace Glue {

class LoadEditorGUI
{
private:
    Irrlicht::Component* irrComp;
    EditorGUI::Component* guiComp;
    Avatar::Component* avComp;

public:
    LoadEditorGUI(
        Irrlicht::Component* irrComp,
        EditorGUI::Component* guiComp,
        Avatar::Component* avComp
    );
    ~LoadEditorGUI();
};

}
