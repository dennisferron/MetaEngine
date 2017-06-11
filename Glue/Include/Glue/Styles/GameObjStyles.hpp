#pragma once

#include "GameObjStyle.hpp"

namespace Glue::GameObjStyles {

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
        int xTiles = 15;
        int zTiles = 15;
        int xHills = 2;
        int zHills = 1;
        int xTextureRepeat = 1;
        int zTextureRepeat = 1;
    };

    struct PlaneStyle : GameObjStyle
    {
        PlaneStyle();
        int xTiles = 15;
        int zTiles = 15;
        int xTextureRepeat = 1;
        int zTextureRepeat = 1;
    )

    struct WallStyle : CylStyle  // I believe this makes a vertical pipe shaped obstacle...
    {
        WallStyle();
    };

    struct GeneratorStyle : GameObjStyle
    {
        GeneratorStyle();
        GameObjStyle* spawnStyle;
    };

    struct ClothStyle : PlaneStyle
    {
        ClothStyle();
    };
}
