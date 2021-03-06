cmake_minimum_required(VERSION 3.13)
project(Glue)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/../cmake
)

include(UseBoost)

add_library(Glue
        Include/Glue/Animators/CustomAnimatorTypes.hpp
        Include/Glue/Animators/KinematicAnimator.hpp
        Include/Glue/Animators/LockAnimator.hpp
        Include/Glue/Animators/PhysicsAnimator.hpp
        Include/Glue/Avatar/AvatarInterfaces.hpp
        Include/Glue/Avatar/AvatarAttribute.hpp
        Include/Glue/Avatar/AvatarComponent.hpp
        Include/Glue/Avatar/Camera.hpp
        Include/Glue/Avatar/KeyInputs.hpp
        Include/Glue/Avatar/PlayerStyle.hpp
        Include/Glue/Bullet/BulletAttribute.hpp
        Include/Glue/Bullet/BulletComponent.hpp
        Include/Glue/Bullet/BulletInterfaces.hpp
        Include/Glue/Bullet/ConstraintBuilder.hpp
        Include/Glue/Bullet/ConstraintObj.hpp
        Include/Glue/Bullet/PhysicsConstraints.hpp
        Include/Glue/Bullet/PhysicsShapes.hpp
        Include/Glue/Bullet/ScriptedWorldManager.hpp
        Include/Glue/Bullet/Sense.hpp
        Include/Glue/Constants.hpp
        Include/Glue/Desteer/Desteer.hpp
        Include/Glue/Desteer/Steering.hpp
        Include/Glue/EditorGUI/EditorGUI.hpp
        Include/Glue/EditorGUI/EditorGUIComponent.hpp
        Include/Glue/EditorGUI/Toolbar.hpp
        Include/Glue/Glue.hpp
        Include/Glue/Interactions/Component/AvatarTime.hpp
        Include/Glue/Interactions/Component/BulletTime.hpp
        Include/Glue/Interactions/Component/DebugDrawer.hpp
        Include/Glue/Interactions/Component/IrrlichtBulletDebugDrawer.hpp
        Include/Glue/Interactions/Component/IrrlichtKeyInput.hpp
        Include/Glue/Interactions/Component/IrrlichtTime.hpp
        Include/Glue/Interactions/Component/LoadEditorGUI.hpp
        Include/Glue/Interactions/Link/BulletMouseDrag.hpp
        Include/Glue/Interactions/Link/CameraFollowObject.hpp
        Include/Glue/Interactions/Link/IrrlichtMouseDrag.hpp
        Include/Glue/Interactions/Link/SelectNode.hpp
        Include/Glue/Interactions/Node/AddScriptObjAnim.hpp
        Include/Glue/Interactions/Node/IrrlichtCamera.hpp
        Include/Glue/Interactions/Node/MotionState.hpp
        Include/Glue/Interactions/Node/PlayerNoPhysSleep.hpp
        Include/Glue/Interactions/Node/PlayerPhysics.hpp
        Include/Glue/Irrlicht/Assets.hpp
        Include/Glue/Irrlicht/Camera.hpp
        Include/Glue/Irrlicht/DisplayShapes.hpp
        Include/Glue/Irrlicht/IrrlichtInterfaces.hpp
        Include/Glue/Irrlicht/IrrlichtAttribute.hpp
        Include/Glue/Irrlicht/IrrlichtComponent.hpp
        Include/Glue/Irrlicht/UserInterface/EventDispatch.hpp
        Include/Glue/Irrlicht/UserInterface/GuiEvents.hpp
        Include/Glue/Irrlicht/UserInterface/Keyboard.hpp
        Include/Glue/Irrlicht/UserInterface/Menu.hpp
        Include/Glue/Irrlicht/UserInterface/Mouse.hpp
        Include/Glue/Irrlicht/UserInterface/MouseDragLinkAttribute.hpp
        Include/Glue/Irrlicht/UserInterface/SceneNodeSelector.hpp
        Include/Glue/Irrlicht/UserInterface/UserInterface.hpp
        Include/Glue/LevelSystem/LevelEditor.hpp
        Include/Glue/LevelSystem/LevelSystem.hpp
        Include/Glue/LevelSystem/Props.hpp
        Include/Glue/LevelSystem/Terrain.hpp
        Include/Glue/LevelSystem/Tile.hpp
        Include/Glue/MeshTools/LinkSplitter.hpp
        Include/Glue/MeshTools/MeshTools.hpp
        Include/Glue/MeshTools/PossibleVertex.hpp
        Include/Glue/MeshTools/SoftBodyMeshSynchronizer.hpp
        Include/Glue/MeshTools/SurfaceQuadTree.hpp
        Include/Glue/Model/Graph.hpp
        Include/Glue/Model/Link.hpp
        Include/Glue/Model/ModelInterfaces.hpp
        Include/Glue/Model/Node.hpp
        Include/Glue/Model/Structure.hpp
        Include/Glue/Model/TimeComponent.hpp
        Include/Glue/Startup.hpp
        Include/Glue/Styles/ConstraintStyle.hpp
        Include/Glue/Styles/ConstraintStyles.hpp
        Include/Glue/Styles/GameObjStyle.hpp
        Include/Glue/Styles/GameObjStyles.hpp
        Include/Glue/Styles/GearConstraint.hpp
        Include/Glue/Styles/LinkStyle.hpp
        Include/Glue/Styles/LinkStyles.hpp
        Include/Glue/Styles/MountStyle.hpp
        Include/Glue/Styles/Styles.hpp
        Include/Glue/UserInterface/MainWindow.hpp
        Include/Glue/UserInterface/Menu.hpp
        Include/Glue/UserInterface/UserInterface.hpp
        Include/Glue/UserInterface/UserInterfaceRepresentation.hpp
        Source/Animators/KinematicAnimator.cpp
        Source/Animators/LockAnimator.cpp
        Source/Animators/PhysicsAnimator.cpp
        Source/Animators/ScriptObjAnimator.cpp
        Source/Avatar/AvatarAttribute.cpp
        Source/Avatar/AvatarComponent.cpp
        Source/Avatar/Camera.cpp
        Source/Avatar/KeyInputs.cpp
        Source/Avatar/PlayerStyle.cpp
        Source/Bullet/BulletAttribute.cpp
        Source/Bullet/BulletComponent.cpp
        Source/Bullet/ConstraintBuilder.cpp
        Source/Bullet/ConstraintObj.cpp
        Source/Bullet/PhysicsShapes.cpp
        Source/Bullet/ScriptedWorldManager.cpp
        Source/Bullet/Sense.cpp
        Source/Desteer/Desteer.cpp
        Source/Desteer/Steering.cpp
        Source/EditorGUI/EditorGUI.cpp
        Source/EditorGUI/EditorGUIComponent.cpp
        Source/EditorGUI/Toolbar.cpp
        Source/Glue.cpp
        Source/Interactions/Component/AvatarTime.cpp
        Source/Interactions/Component/BulletTime.cpp
        Source/Interactions/Component/DebugDrawer.cpp
        Source/Interactions/Component/IrrlichtBulletDebugDrawer.cpp
        Source/Interactions/Component/IrrlichtKeyInput.cpp
        Source/Interactions/Component/IrrlichtTime.cpp
        Source/Interactions/Component/LoadEditorGUI.cpp
        Source/Interactions/Link/BulletMouseDrag.cpp
        Source/Interactions/Link/CameraFollowObject.cpp
        Source/Interactions/Link/IrrlichtMouseDrag.cpp
        Source/Interactions/Link/SelectNode.cpp
        Source/Interactions/Node/AddScriptObjAnim.cpp
        Source/Interactions/Node/IrrlichtCamera.cpp
        Source/Interactions/Node/MotionState.cpp
        Source/Interactions/Node/PlayerNoPhysSleep.cpp
        Source/Interactions/Node/PlayerPhysics.cpp
        Source/Irrlicht/Assets.cpp
        Source/Irrlicht/Camera.cpp
        Source/Irrlicht/DisplayShapes.cpp
        Source/Irrlicht/IrrlichtAttribute.cpp
        Source/Irrlicht/IrrlichtComponent.cpp
        Source/Irrlicht/UserInterface/EventDispatch.cpp
        Source/Irrlicht/UserInterface/GuiEvents.cpp
        Source/Irrlicht/UserInterface/Keyboard.cpp
        Source/Irrlicht/UserInterface/Menu.cpp
        Source/Irrlicht/UserInterface/Mouse.cpp
        Source/Irrlicht/UserInterface/MouseDragLinkAttribute.cpp
        Source/Irrlicht/UserInterface/SceneNodeSelector.cpp
        Source/Irrlicht/UserInterface/UserInterface.cpp
        Source/LevelSystem/LevelEditor.cpp
        Source/LevelSystem/LevelSystem.cpp
        Source/LevelSystem/Props.cpp
        Source/LevelSystem/Terrain.cpp
        Source/LevelSystem/Tile.cpp
        Source/MeshTools/HillMesh.cpp
        Source/MeshTools/LinkSplitter.cpp
        Source/MeshTools/MeshTools.cpp
        Source/MeshTools/PossibleVertex.cpp
        Source/MeshTools/SoftBodyMeshSynchronizer.cpp
        Source/MeshTools/SurfaceQuadTree.cpp
        Source/Model/Graph.cpp
        Source/Model/Link.cpp
        Source/Model/Node.cpp
        Source/Model/Structure.cpp
        Source/Model/TimeComponent.cpp
        Source/Startup.cpp
        Source/Styles/ConstraintStyle.cpp
        Source/Styles/ConstraintStyles.cpp
        Source/Styles/GameObjStyle.cpp
        Source/Styles/GameObjStyles.cpp
        Source/Styles/GearConstraint.cpp
        Source/Styles/LinkStyle.cpp
        Source/Styles/LinkStyles.cpp
        Source/Styles/MountStyle.cpp
        Source/Styles/Styles.cpp
        Source/UserInterface/MainWindow.cpp
        Source/UserInterface/Menu.cpp
        Source/UserInterface/UserInterface.cpp
        Source/UserInterface/UserInterfaceRepresentation.cpp
        Include/Glue/Avatar/AvatarInterfaces.hpp Include/Glue/Model/ITimeComponent.hpp Include/Glue/Bullet/BulletShape.hpp Source/Bullet/BulletShape.cpp Include/Glue/Model/Shape.hpp Source/Model/Shape.cpp Include/Glue/Utility/variant_helpers.hpp Include/Glue/Styles/ShapeStyle.hpp Include/Glue/Engine.hpp Source/Engine.cpp Include/Glue/Factory/ShapeFactory.hpp Source/Factory/ShapeFactory.cpp Include/Glue/Factory/NodeFactory.hpp Source/Factory/NodeFactory.cpp Include/Glue/Factory/LinkFactory.hpp Source/Factory/LinkFactory.cpp)

# Note:  Order of libraries in this list matters.  I know LinearMath and BulletCollision go at the bottom.
#  I'm less sure about the order of the rest of the Bullet libraries.
target_link_libraries( Glue PUBLIC
        ThinPlateSpline
        Irrlicht
        Bullet3Common
        BulletInverseDynamics
        BulletSoftBody
        BulletDynamics
        BulletCollision
        LinearMath
        sqlite
)

target_include_directories(Glue PUBLIC Include)
target_include_directories(Glue PUBLIC ../ThinPlateSpline/Include)
target_include_directories(Glue PUBLIC ../irrlicht/include)
target_include_directories(Glue PUBLIC ../bullet3/src)
target_include_directories(Glue PUBLIC ../bullet3/src/BulletDynamics/Dynamics)
target_include_directories(Glue PUBLIC ../bullet3/src/LinearMath)

#add_dependencies(Glue generate-gamedata-headers)
target_include_directories(Glue PUBLIC ${CMAKE_BINARY_DIR}/Data)
