#pragma once

namespace Glue::Props {

using NodeStyle = Glue::GameObjStyle;
using LinkStyle = Glue::LinkStyle;

struct Stage {
    Stage();
    Structure* build();
};

struct Tree {
    Tree();

    NodeStyle* base;
    LinkStyle* joint;
    NodeStyle* trunk
    NodeStyle* top;

    Structure* build();
};

struct Snake {
    Snake();

    NodeStyle* segmentStyle;
    LinkStyle* jointStyle;
    LinkStyle* leftJointStyle;
    LinkStyle* rightJointStyle;
    NodeStyle* headStyle;
    LinkStyle* noseHeadJoint;
    NodeStyle* noseStyle;

    Structure* build();
    static Node* configure(Graph* graph, Structure* snake);
    static void setMotors(Node* segment, int count);
};

struct Robot {
    Robot();

    NodeStyle* shoulderBall;
    LinkStyle* shoulderToUpperArm;
    NodeStyle* upperArm;
    LinkStyle* upperArmToElbow;
    NodeStyle* elbowBall;
    LinkStyle* elbowToForeArm;
    NodeStyle* foreArm;
    NodeStyle* torso;
    LinkStyle* torsoToLeftShoulder;
    LinkStyle* torsoToRightShoulder;
    LinkStyle* torsoToBase;
    NodeStyle* base;
    NodeStyle* head;
    LinkStyle* headToTorso;
    LinkStyle* leftAxle;
    LinkStyle* rightAxle;
    NodeStyle* leftWheel;
    NodeStyle* rightWheel;

    Structure* build();
    Node* configure(Graph* graph, Structure* robotStructure);
};

struct Cannon {
    Cannon();
    Structure* build();
    static Node* configure(Graph* graph, Structure* cannon);

    NodeStyle* hub;
    NodeStyle* barrel;
    GeneratorStyle* tip;
};

struct Car {

    NodeStyle* leftWheel;
    LinkStyle* leftAxle;
    NodeStyle* rightWheel;
    LinkStyle* rightAxle;

    NodeStyle* carBody;

    LinkStyle* gearAxle;
    NodeStyle* gearSlotStyle;

    Structure* build();
    static Node* configure(Graph* graph, Structure* car);
};

struct Elevator {

    Elevator(Scalar x, Scalar y);

    NodeStyle* elevatorStyle;

    Structure* build();
    static Node* configure(Graph* graph, Structure* elevator);

    LinkStyle* standOnElevator;
};

struct Box {
    Box();
    NodeStyle* style;
    static Node* configure(Graph* graph, NodeStyle* style);
    Structure* build();
};

struct Dwarf {
    Dwarf();
    NodeStyle* style;
    static Node* configure(Graph* graph, Structure* dwarf);
    Node* loadL3DTMesh();
};

struct Skybox {
    Skybox();
    NodeStyle* style;
    static Node* configure(Graph* graph, Structure* skybox);
};

struct Props
{
    Terrain* terrain;
    Skybox* skybox;

    Props& loadLevel();
    Props& loadLevelOld();
    Props& loadSkybox();

    Props& testSoftBody(Graph* graph);

};

}
