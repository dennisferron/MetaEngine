#pragma once

#include "Glue/Irrlicht/IrrlichtInterfaces.hpp"
#include "Glue/EditorGUI/EditorGUIComponent.hpp"
#include "Glue/Avatar/AvatarInterfaces.hpp"

namespace Glue {

class LoadEditorGUI
{
private:
    Irrlicht::IIrrlichtComponent* irrComp;
    EditorGUI::EditorGUIComponent* guiComp;
    Avatar::IAvatarComponent* avComp;

public:
    LoadEditorGUI(
        Irrlicht::IIrrlichtComponent* irrComp,
        EditorGUI::EditorGUIComponent* guiComp,
        Avatar::IAvatarComponent* avComp
    );
    ~LoadEditorGUI();
};

}
