
#include "Glue/LevelSystem/Terrain.hpp"
#include "irrlicht.h"
#include "Glue/MeshTools/MeshTools.hpp"
#include "ThinPlateSpline/ThinPlateQuilt.hpp"
#include "Glue/Styles/GameObjStyles.hpp"

using namespace std;
using namespace boost;

using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

using namespace TPS;

namespace {

    float get_random_float(float min, float max)
    {
            static boost::minstd_rand algorithm;
            static boost::uniform_real<float> range(0.0f, 1.0f);
            static boost::variate_generator<boost::minstd_rand&, boost::uniform_real<float> > generator(algorithm, range);
            float result = (max-min)*generator()+min;
            return result;
    }
}

namespace Glue {

    Terrain::Terrain()
    {
        worldSizeX = 64;
        worldSizeY = 64;
        levelRect =
            rectf(
                vector2df(-worldSizeX/2f, -worldSizeY/2f),
                dimension2df(worldSizeX, worldSizeY)
            );
        numTilesX = 4;
        numTilesY = 4;

        tileDimensions = dimension2df(
            levelRect.getWidth() / numTilesX, levelRect.getHeight() / numTilesY);
    }

    void Terrain::load()
    {
        tileArray.resize(numTilesX * numTilesY);

        // The num tiles in meshes and the surface need not be identical.
        surfaceCols = numTilesX;
        surfaceRows = numTilesY;
        surfaceMin = Vec(levelRect.UpperLeftCorner.X, 0, levelRect.UpperLeftCorner.Y);
        surfaceMax = Vec(levelRect.LowerRightCorner.X, 0, levelRect.LowerRightCorner.Y);

        tps = new ThinPlateQuilt(surfaceCols, surfaceRows, surfaceMin, surfaceMax);

        for (int i=0; i<100; i++)
        {
            float cpx = get_random_float(
                    levelRect.UpperLeftCorner.X, levelRect.LowerRightCorner.X);
            float cpy = get_random_float(
                    levelRect.UpperLeftCorner.Y, levelRect.LowerRightCorner.Y);

            float h = get_random_float(-11.0, 5.0);

            tps->addControlPoint(
                    Vec(cpx, h, cpy)
            );

            BallStyle controlPointStyle;
            controlPointStyle
                    .setPhysShape("none")
                    .setSize(0.5)
                    .setIsMouseDraggable(true)
                    .setPos(cpx, cpy, h);

            graph->addNode(controlPointStyle);
        }

        tps->refresh();

        surface = new SurfaceQuadTree(levelRect, tps, "Root");

        // Initial grid placement
        surface->split(initialSplit);

        // Split the grid to fit the path more closely
        surface->fit(minFitSize, {skyCutZ, pathMinZ, pathMaxZ});

        for (int x=0; x<numTilesX; x++)
        {
            //writeln("Loading terrain tile column ", x, " of ", numTilesX)
            for (int y=0; y<numTilesY; y++)
            {
                Scalar offset = 0.1; // this ensures right/bottom tile boundaries are triangulated.
                vector2df tilePos(x * tileDimensions get_Width + levelRect get_UpperLeftCorner get_X + offset,
                                         y * tileDimensions get_Height + levelRect get_UpperLeftCorner get_Y + offset);
                rectf tileRect(tilePos, tileDimensions);
                Tile tile;
                tile
                    .setGraph(graph)
                    .setMeshMan(meshMan)
                    .setTileRect(tileRect)
                    .setSurface(surface)
                    .setPathMinZ(pathMinZ)
                    .setPathMaxZ(pathMaxZ)
                    .setSkyCutZ(skyCutZ)
                    .refresh();
                tileArray[tileIndex(x,y)] = tile;
            }
        }
    }

    std::size_t Terrain::tileIndex(int x, int y) const
    {
        if (x >= numTilesX)
            throw std::logic_error("x out of bounds");

        if( y >= numTilesY)
            throw std::logic_error("y out of bounds");

        std::size result = y*numTilesX + x;

        if (result >= tileArray.size())
            throw std::logic_error("tileIndex out of bounds.");

        return result;
    }

}  // namespace Glue
