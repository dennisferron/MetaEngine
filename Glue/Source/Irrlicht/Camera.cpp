#include "Glue/Irrlicht/Camera.hpp"

using namespace irr;
using namespace irr::core;
using namespace irr::video;

namespace Glue::Irrlicht
{

    Camera::Camera(
            irr::scene::ISceneManager* smgr,
            irr::video::IVideoDriver* driver)
        : smgr(smgr), driver(driver)
    {

    }

    void Camera::createNode()
    {

/*
	cameraNode = smgr addCameraSceneNode(
		nil, // parent
		vector3df tmpWithXYZ(0, 0, distZ), // position
		vector3df tmpWithXYZ(0, -10, 0), // lookat
		-1, // id
		true  // makeActive
	)

    cameraNode setFOV(0.1*TAU)

*/
        cameraNode = smgr->addCameraSceneNodeMaya(
                nullptr,    // parent
                -1000.0, // rotate speed
                200.0, // zoom speed
                150.0, // translation speed
                -1, // id
                20.0, // distance
                true // makeActive
        );

        cameraNode->setPosition(vector3df(0, 0, 30));
    }

void Camera::update()
{
    if (targetIrrAttrib != nullptr)
    {
        auto target = targetIrrAttrib->getSceneNode()->getAbsolutePosition();

        auto tx = target.X;
        auto ty = target.Y;

        if (tx < boxX - boxXSize/2) boxX = tx + boxXSize/2;
        if (ty < boxY - boxYSize/2) boxY = ty + boxYSize/2;
        if (tx > boxX + boxXSize/2) boxX = tx - boxXSize/2;
        if (ty > boxY + boxYSize/2) boxY = ty - boxYSize/2;

        cameraNode->setPosition(vector3df(boxX, boxY+5, distZ));
        cameraNode->setTarget(vector3df(boxX, boxY, 0));

        draw();
    }
}

void Camera::draw()
{
    driver->draw3DLine(
            vector3df(boxX - boxXSize / 2, boxY - boxYSize / 2, 0),
            vector3df(boxX - boxXSize / 2, boxY + boxYSize / 2, 0),
            SColor(255, 255, 255, 255)
    );

    driver->draw3DLine(
            vector3df(boxX + boxXSize / 2, boxY - boxYSize / 2, 0),
            vector3df(boxX + boxXSize / 2, boxY + boxYSize / 2, 0),
            SColor(255, 255, 255, 255)
    );

    driver->draw3DLine(
            vector3df(boxX - boxXSize / 2, boxY - boxYSize / 2, 0),
            vector3df(boxX + boxXSize / 2, boxY - boxYSize / 2, 0),
            SColor(255, 255, 255, 255)
    );

    driver->draw3DLine(
            vector3df(boxX - boxXSize / 2, boxY + boxYSize / 2, 0),
            vector3df(boxX + boxXSize / 2, boxY + boxYSize / 2, 0),
            SColor(255, 255, 255, 255)
    );
}


}