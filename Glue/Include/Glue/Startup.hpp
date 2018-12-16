#pragma once

#include <string>
#include <memory>

// Would include LM protos and constants
//#include "Glue/PredefinedValues.hpp"

namespace irr { namespace core {

class vector3df;
class line3df;

}}

namespace Glue { namespace Model {

class Graph;

}}


namespace Glue {

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
