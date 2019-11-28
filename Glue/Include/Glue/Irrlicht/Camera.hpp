#pragma once

#include "Glue/Constants.hpp"
#include "SColor.h"
#include "IrrlichtDevice.h"
#include "ICameraSceneNode.h"
#include "Glue/Irrlicht/IrrlichtAttribute.hpp"

namespace Glue { namespace Irrlicht {

class Camera
{
private:

	Scalar boxX = 0;
	Scalar boxY = 0;

	Scalar boxXSize = 5;
	Scalar boxYSize = 5;

	irr::scene::ICameraSceneNode* cameraNode = nullptr;
	IrrlichtAttribute* targetIrrAttrib = nullptr;

    irr::scene::ISceneManager* smgr;
    irr::video::IVideoDriver* driver;

    Scalar distZ = 20;

public:
    Camera(
        irr::scene::ISceneManager* smgr,
        irr::video::IVideoDriver* driver);
    void createNode();
    void update();
    void draw();
};

}}
