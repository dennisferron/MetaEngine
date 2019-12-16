#include "Glue/Irrlicht/Assets.hpp"


namespace Glue::Irrlicht
{
    irr::io::path Assets::getPath(std::string const& assetFile) const
    {
        std::string narrow_string = assetPath + "/" + assetFile;
        std::wstring wide_string = std::wstring(narrow_string.begin(), narrow_string.end());
        const wchar_t* ptr = wide_string.c_str();
        auto result = irr::io::path(ptr);
        return result;
    }

    irr::video::ITexture* Assets::loadTextureFromFile(std::string const& filename) const
    {
        irr::io::path fsStr = getPath(filename);
        irr::video::ITexture* texture = driver->getTexture(fsStr);
        return texture;
    }

    irr::video::IImage* Assets::loadImageFromFile(std::string const& filename) const
    {
        irr::io::path fsStr = getPath(filename);
        irr::video::IImage* image = driver->createImageFromFile(fsStr);
        return image;
    }
}