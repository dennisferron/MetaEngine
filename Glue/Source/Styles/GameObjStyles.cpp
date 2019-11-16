#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/GameObjStyles.hpp"

#include <string>

using namespace std;

namespace Glue::GameObjStyles {

    map<string, GameObjStyle> predefined_styles;

    GameObjStyle EmptyStyle()
    {
        return predefined_styles["Empty"];
    }

    GameObjStyle BoxStyle()
    {
        return predefined_styles["Box"];
    }

    GameObjStyle BallStyle()
    {
        return predefined_styles["Ball"];
    }

    GameObjStyle CylStyle()
    {
        return predefined_styles["Cyl"];
    }

    GameObjStyle CylXStyle()
    {
        return predefined_styles["CylX"];
    }

    GameObjStyle CylZStyle()
    {
        return predefined_styles["CylZ"];
    }

    GameObjStyle ConeStyle()
    {
        return predefined_styles["Cone"];
    }

    GameObjStyle ConeXStyle()
    {
        return predefined_styles["ConeX"];
    }

    GameObjStyle ConeZStyle()
    {
        return predefined_styles["ConeZ"];
    }

    GameObjStyle SkyboxStyle()
    {
        return predefined_styles["Skybox"];
    }

    GameObjStyle HillStyle()
    {
        return predefined_styles["Hill"];
    }

    GameObjStyle PlaneStyle()
    {
        return predefined_styles["Plane"];
    }

    GameObjStyle WallStyle()
    {
        return predefined_styles["Wall"];
    }

    GameObjStyle ClothStyle()
    {
        return predefined_styles["Cloth"];
    }
}
//EmptyStyle::EmptyStyle()
//    : GameObjStyle(ObjShapes::none)
//{
//}
//
//BoxStyle::BoxStyle()
//    : GameObjStyle(ObjShapes::box)
//{
//}
//
//BallStyle::BallStyle()
//    : GameObjStyle(ObjShapes::ball)
//{
//}
//
//CylStyle::CylStyle()
//    : GameObjStyle(ObjShapes::cyl)
//{
//}
//
//CylXStyle::CylXStyle()
//    : GameObjStyle(ObjShapes::cylX)
//{
//}
//
//CylZStyle::CylZStyle()
//    : GameObjStyle(ObjShapes::cylZ)
//{
//}
//
//ConeStyle::ConeStyle()
//    : GameObjStyle(ObjShapes::cone)
//{
//}
//
//ConeXStyle::ConeXStyle()
//    : GameObjStyle(ObjShapes::coneX)
//{
//}
//
//ConeZStyle::ConeZStyle()
//    : GameObjStyle(ObjShapes::coneZ)
//{
//}
//
//SkyboxStyle::SkyboxStyle()
//    : GameObjStyle(ObjShapes::skybox, ObjShapes::none)
//{
//}

//HillStyle_t::HillStyle_t()
//    : GameObjStyleBase(ObjShapes::hills)
//{
//    gameObjType = GameObjTypes::static_;
//    mass = 0;
//    setSize(1.0, 2.0, 1.0);
//    xTiles = 15;
//    zTiles = 15;
//    xHills = 2;
//    zHills = 1;
//    xTextureRepeat = 1;
//    zTextureRepeat = 1;
//}
//
//PlaneStyle_t::PlaneStyle_t()
//    : GameObjStyleBase(ObjShapes::plane, ObjShapes::mesh)
//{
//    gameObjType = GameObjTypes::static_;
//    margin = 0.1;
//    mass = 0;
//    setSize(1.0f, 0.0f, 1.0f);
//    xTiles = 15;
//    zTiles = 15;
//    xTextureRepeat = 1;
//    zTextureRepeat = 1;
//}

//WallStyle::WallStyle()
//{
//    // TODO: Not sure about this one:
//    //dispShape = ObjShapes::mesh;
//
//    setColor(200, 60, 240);
//    mass = 0;
//    radius = 10;
//    length = 1000;
//}

//ClothStyle::ClothStyle()
//{
//    gameObjType = GameObjTypes::soft;
//}

