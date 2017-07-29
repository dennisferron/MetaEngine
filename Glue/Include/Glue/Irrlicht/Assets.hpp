#pragma once

#include <memory>

namespace irr { video {
    class ITexture;
    class IImage;
}}

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
    ITexture* loadTextureFromFile(std::string const& filename) const;
    IImage* loadImageFromFile(std::string const& filename) const;
};

}}
