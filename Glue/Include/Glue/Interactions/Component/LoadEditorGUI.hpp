#pragma once

#include "Glue/Irrlicht/IrrlichtComponent.hpp"
#include "Glue/EditorGUI/EditorGUIComponent.hpp"
#include "Glue/Avatar/AvatarComponent.hpp"

namespace Glue {

class LoadEditorGUI
{
private:
    Irrlicht::IrrlichtComponent* irrComp;
    EditorGUI::EditorGUIComponent* guiComp;
    Avatar::AvatarComponent* avComp;

public:
    LoadEditorGUI(
        Irrlicht::IrrlichtComponent* irrComp,
        EditorGUI::EditorGUIComponent* guiComp,
        Avatar::AvatarComponent* avComp
    );
    ~LoadEditorGUI();
};

}
