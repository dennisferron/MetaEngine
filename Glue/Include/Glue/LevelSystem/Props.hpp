#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Model/ModelInterfaces.hpp"
#include "Glue/LevelSystem/Terrain.hpp"
#include "Glue/Styles/GameObjStyles.hpp"

#include "sqlite3.h"

namespace Glue {

    class Props
    {
    public:
        Props(sqlite3* db);

        using NodeStyle = Glue::GameObjStyle;
        using LinkStyle = Glue::LinkStyle;

        struct Stage
        {
            Stage();

            IStructure *build();
        };

        struct Tree
        {
            Tree();

            NodeStyle base;
            LinkStyle joint;
            NodeStyle trunk;
            NodeStyle top;

            IStructure *build();
        };

        struct Snake
        {
            Snake();

            NodeStyle segmentStyle;
            LinkStyle jointStyle;
            LinkStyle leftJointStyle;
            LinkStyle rightJointStyle;
            NodeStyle headStyle;
            LinkStyle noseHeadJoint;
            NodeStyle noseStyle;

            IStructure *build();

            INode *configure(IGraph *graph, IStructure *snake);
            void setMotors(INode *segment, int count);
        };

        struct Robot
        {
            Robot();

            NodeStyle shoulderBall;
            LinkStyle shoulderToUpperArm;
            NodeStyle upperArm;
            LinkStyle upperArmToElbow;
            NodeStyle elbowBall;
            LinkStyle elbowToForeArm;
            NodeStyle foreArm;
            NodeStyle torso;
            LinkStyle torsoToLeftShoulder;
            LinkStyle torsoToRightShoulder;
            LinkStyle torsoToBase;
            NodeStyle base;
            NodeStyle head;
            LinkStyle headToTorso;
            LinkStyle leftAxle;
            LinkStyle rightAxle;
            NodeStyle leftWheel;
            NodeStyle rightWheel;

            IStructure *build();

            INode *configure(IGraph *graph, IStructure *robotIStructure);
        };

        struct Cannon
        {
            Cannon();

            IStructure *build();

            INode *configure(IGraph *graph, IStructure *cannon);

            NodeStyle hub;
            NodeStyle barrel;
            // GameObjStyles::GeneratorStyle<GameObjStyles::BallStyle> tip;
            GameObjStyle tip;
        };

        struct Car
        {

            NodeStyle leftWheel;
            LinkStyle leftAxle;
            NodeStyle rightWheel;
            LinkStyle rightAxle;

            NodeStyle carBody;

            LinkStyle gearAxle;
            NodeStyle gearSlotStyle;

            IStructure *build();

            INode *configure(IGraph *graph, IStructure *car);
        };

        struct Elevator
        {

            Elevator(Scalar x, Scalar y);

            NodeStyle elevatorStyle;

            IStructure *build();

            INode *configure(IGraph *graph, IStructure *elevator);

            LinkStyle standOnElevator;
        };

        struct Box
        {
            Box();

            NodeStyle style;

            INode *configure(IGraph *graph, NodeStyle style);

            IStructure *build();
        };

        struct Dwarf
        {
            Dwarf();

            NodeStyle style;

            INode *configure(IGraph *graph, IStructure *dwarf);

            INode *loadL3DTMesh();
        };

        struct Skybox
        {
            Skybox();

            NodeStyle style;

            INode *configure(IGraph *graph, IStructure *skybox);
        };

        struct TestProps
        {
            Terrain *terrain;
            Skybox *skybox;

            void loadLevel();

            void loadLevelOld();

            void loadSkybox();

            void testSoftBody(IGraph *graph);

        };
    };
}
