// Copyright 2008-2013, 2017 Dennis Ferron

#include "btBulletDynamicsCommon.h"

#pragma once

namespace irr { namespace video {
    class IVideoDriver;
}}

namespace Glue {

class IrrlichtBulletDebugDrawer : public btIDebugDraw
{
private:
    irr::video::IVideoDriver* driver;
    int debugMode;

public:
    IrrlichtBulletDebugDrawer(irr::video::IVideoDriver* driver_);
    ~IrrlichtBulletDebugDrawer();
    virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);
    virtual void reportErrorWarning(const char* warningString);
    virtual void draw3dText(const btVector3 &location, const char *textString);
    virtual void setDebugMode(int debugMode);
    virtual int getDebugMode() const;
	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

};

}
