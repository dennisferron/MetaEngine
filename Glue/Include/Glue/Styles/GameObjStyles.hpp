#pragma once

#include "GameObjStyle.hpp"

namespace Glue { namespace GameObjStyles {

    struct EmptyStyle : GameObjStyle
    {
        EmptyStyle();
    };

    struct BoxStyle : GameObjStyle
    {
        BoxStyle();
    };

    struct BallStyle : GameObjStyle
    {
        BallStyle();
    };

    struct CylStyle : GameObjStyle
    {
        CylStyle();
    };

    struct CylXStyle : GameObjStyle
    {
        CylXStyle();
    };

    struct CylZStyle : GameObjStyle
    {
        CylZStyle();
    }

    struct ConeStyle : GameObjStyle
    {
        ConeStyle();
    };

    struct ConeXStyle : GameObjStyle
    {
        ConeXStyle();
    };

    struct ConeZStyle : GameObjStyle
    {
        ConeZStyle();
    };

    struct SkyboxStyle : GameObjStyle
    {
        SkyboxStyle();
    };

    struct HillStyle : GameObjStyle
    {
        HillStyle();
        int xTiles;
        int zTiles;
        int xHills;
        int zHills;
        int xTextureRepeat;
        int zTextureRepeat;
    };

    struct PlaneStyle : GameObjStyle
    {
        PlaneStyle();
        int xTiles;
        int zTiles;
        int xTextureRepeat;
        int zTextureRepeat;
    };

    struct WallStyle : CylStyle  // I believe this makes a vertical pipe shaped obstacle...
    {
        WallStyle();
    };

    template <typename T>
    struct GeneratorStyle : GameObjStyle
    {
        T spawnStyle;

        GeneratorStyle()
            : GameObjStyle(ObjShapes::none)
        {
            isKinematic = true;
            collisionGroup = 0;  // TODO:  make a group just for generators
            collisionMask = 0;

            spawnStyle.setVel(0, 30, 0);
        }
    };

    struct ClothStyle : PlaneStyle
    {
        ClothStyle();
    };
}}
