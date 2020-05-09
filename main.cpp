/*
The program will show how to use the
basics of the VideoDriver, the GUIEnvironment and the
SceneManager.

To use the engine, we will have to include the header file
irrlicht.h, which can be found in the Irrlicht Engine SDK
directory \include.
*/
#include <irrlicht.h>

/*
In the Irrlicht Engine, everything can be found in the namespace
'irr'. So if you want to use a class of the engine, you have to
write an irr:: before the name of the class. For example to use
the IrrlichtDevice write: irr::IrrlichtDevice. To get rid of the
irr:: in front of the name of every class, we tell the compiler
that we use that namespace from now on, and we will not have to
write that 'irr::'.
*/
using namespace irr;

/*
There are 5 sub namespaces in the Irrlicht Engine. Take a look
at them, you can read a detailed description of them in the
documentation by clicking on the top menu item 'Namespace List'
or using this link: http://irrlicht.sourceforge.net/docu/namespaces.html.
Like the irr Namespace, we do not want these 5 sub namespaces now,
to keep this example simple. Hence we tell the compiler again
that we do not want always to write their names:
*/
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"

#include "Glue/MeshTools/MeshTools.hpp"

#include <iostream>

#include "Glue/Startup.hpp"

/*
This is the main method. We can use void main() on every platform.
On Windows platforms, we could also use the WinMain method
if we would want to get rid of the console window, which pops up when
starting a program with main(), but to keep this example simple,
we use main().
*/
int main(int argc, char** argv)
{
    try
    {
        Glue::do_startup();
    }
    catch (char const* msg)
    {
        std::cerr << "Caught exception: " << msg;
        return -1;
    }

    return 0;
}

