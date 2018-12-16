// Copyright 2008-2013, 2017 Dennis Ferron

#pragma once

namespace irr { namespace scene { class IMeshBuffer; } }

class btSoftBody;

namespace Glue {

class SoftBodyMeshSynchronizer
{
private:
    btSoftBody* softBody;
    irr::scene::IMeshBuffer* meshBuf;

public:
    SoftBodyMeshSynchronizer(btSoftBody* softBody_, irr::scene::IMeshBuffer* meshBuf_);
    ~SoftBodyMeshSynchronizer();

    void sync();
};

}
