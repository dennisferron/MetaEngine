#pragma once

#include "Glue/Constants.hpp"
#include "SColor.h"
#include "IrrlichtDevice.h"
#include "ICameraSceneNode.h"

namespace Glue { namespace Irrlicht {

class Camera
{
private:

	Scalar boxX;
	Scalar boxY;

	Scalar boxXSize;
	Scalar boxYSize;

	irr::scene::ICameraSceneNode* cameraNode;
	void* targetIrrAttrib;

    irr::scene::ISceneManager* smgr;
    irr::IrrlichtDevice* driver;

    Scalar distZ;

public:
    Camera(
        irr::scene::ISceneManager* smgr,
        irr::IrrlichtDevice* driver);
    void createNode();
    void update();
    void draw();
};

}}
