#pragma once

namespace Glue { namespace Irrlicht {
    Component;
}}

namespace Glue { namespace EditorGUI {
    Component;
}}

namespace Glue { namespace Avatar {
    Component;
}}

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
