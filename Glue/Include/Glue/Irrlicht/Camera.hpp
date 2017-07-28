#pragma once

namespace irr { namespace video {
    class SColor;
}}

namespace irr {
    class IrrlichtDevice;
}

namespace Glue {

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
    void createNode();
    void update();
    void draw();
};

}
