#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/GameObjStyles.hpp"

namespace Glue { namespace GameObjStyles {

EmptyStyle::EmptyStyle()
    : GameObjStyle(ObjShapes::none)
{
}

BoxStyle::BoxStyle()
    : GameObjStyle(ObjShapes::box)
{
}

BallStyle::BallStyle()
    : GameObjStyle(ObjShapes::ball)
{
}

CylStyle::CylStyle()
    : GameObjStyle(ObjShapes::cyl)
{
}

CylXStyle::CylXStyle()
    : GameObjStyle(ObjShapes::cylX)
{
}

CylZStyle::CylZStyle()
    : GameObjStyle(ObjShapes::cylZ)
{
}

ConeStyle::ConeStyle()
    : GameObjStyle(ObjShapes::cone)
{
}

ConeXStyle::ConeXStyle()
    : GameObjStyle(ObjShapes::coneX)
{
}

ConeZStyle::ConeZStyle()
    : GameObjStyle(ObjShapes::coneZ)
{
}

SkyboxStyle::SkyboxStyle()
    : GameObjStyle(ObjShapes::skybox, ObjShapes::none)
{
}

HillStyle::HillStyle()
    : GameObjStyle(ObjShapes::hills)
{
    gameObjType = GameObjTypes::static_;
    mass = 0;
    setSize(1.0, 2.0, 1.0);
    xTiles = 15;
    zTiles = 15;
    xHills = 2;
    zHills = 1;
    xTextureRepeat = 1;
    zTextureRepeat = 1;
}

PlaneStyle::PlaneStyle()
    : GameObjStyle(ObjShapes::plane, ObjShapes::mesh)
{
    gameObjType = GameObjTypes::static_;
    margin = 0.1;
    mass = 0;
    setSize(1.0f, 0.0f, 1.0f)
    xTiles = 15;
    zTiles = 15;
    xTextureRepeat = 1;
    zTextureRepeat = 1;
}

WallStyle::WallStyle()
    : GameObjStyle(ObjShapes::mesh)
{
    setColor(200, 60, 240);
    mass = 0;
    radius = 10;
    length = 1000;
}

ClothStyle::ClothStyle()
{
    gameObjType = GameObjTypes::soft;
}

}}
