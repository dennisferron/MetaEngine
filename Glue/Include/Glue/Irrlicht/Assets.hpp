#pragma once

#include <memory>

#include "ITexture.h"
#include "IImage.h"
#include "IVideoDriver.h"

namespace Glue::Irrlicht {

    class Assets
    {
    private:
        std::string assetPath;
        irr::video::IVideoDriver *driver = nullptr;

    public:

        Assets();

        ~Assets();

        irr::io::path getPath(std::string const &assetFile) const;

        irr::video::ITexture *loadTextureFromFile(std::string const &filename) const;

        irr::video::IImage *loadImageFromFile(std::string const &filename) const;
    };
}
