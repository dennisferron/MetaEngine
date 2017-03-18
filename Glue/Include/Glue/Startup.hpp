#pragma once

#include <string>
#include <memory>

// Would include LM protos and constants
//#include "Glue/PredefinedValues.hpp"

namespace irr { namespace core {

class vector3df;
class line3df;

}}

namespace MetaEngine { namespace Model {

class Graph;

}}


namespace MetaEngine {

struct Constants
{
    static const float TAU := 2*3.1459
    static const int AllFilter 65535
    static const int CameraFilter := 64
    static const float FrameSeconds := 1 / 64
    static const float timeStep := FrameSeconds
    static const int mouseDraggableBitPos  := 31
    static const int mouseDraggableBitMask := (1 << 31)
};

class RootModule
{
public:

    // Don't use "WayUpDir" for new code; instead load textures from
    // the Irrlicht Component Assets object.  For other files,
    // figure out on case-by-case basis where the code should go.
    std::string WayUpDir(std::string const& assetPath);

    // Convenience method
    static std::string vector3dfAsString(irr::core::vector3df const& v);

    // Convenience method
    static std::string line3dfAsString(irr::core::line3df const& line);

    RootModule();

private:

    std::unique_ptr<Model::Graph> graph;
};

}
