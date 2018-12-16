#pragma once

#include <memory>

#include "ITexture.h"
#include "IImage.h"

namespace Glue { namespace Irrlicht {

class Assets
{
private:
    class Impl;
    std::unique_ptr<Impl> impl;

public:

    Assets();
    ~Assets();

    std::string getPath(std::string const& assetFile) const;
    irr::video::ITexture* loadTextureFromFile(std::string const& filename) const;
    irr::video::IImage* loadImageFromFile(std::string const& filename) const;
};

}}
