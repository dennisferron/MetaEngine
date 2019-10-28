
#include "Glue/LevelSystem/Terrain.hpp"
#include "irrlicht.h"
#include "Glue/MeshTools/MeshTools.hpp"
#include "ThinPlateSpline/ThinPlateQuilt.hpp"
#include "Glue/Styles/GameObjStyles.hpp"

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

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

namespace Glue { namespace LevelSystem {

    Terrain::Terrain()
    {
        int worldSizeX = 64;
        int worldSizeY = 64;
        levelRect =
            rectf(
                vector2df(-worldSizeX/2.0f, -worldSizeY/2.0f),
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
        int surfaceCols = numTilesX;
        int surfaceRows = numTilesY;
        auto surfaceMin = Vec(levelRect.UpperLeftCorner.X, 0, levelRect.UpperLeftCorner.Y);
        auto surfaceMax = Vec(levelRect.LowerRightCorner.X, 0, levelRect.LowerRightCorner.Y);

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

            /*GameObjStyles::BallStyle*/ NodeStyle controlPointStyle;
            controlPointStyle
                    //.setPhysShape("none")
                    ->setSize(0.5)
                    //.setIsMouseDraggable(true)
                    .setPos(cpx, cpy, h);
            controlPointStyle->physShape = ObjShapes::none;

            graph->addNode(controlPointStyle);
        }

        tps->refresh();

        surface = new SurfaceQuadTree(levelRect, *tps, "Root");

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
                vector2df tilePos(
                        x * tileDimensions.Width + levelRect.UpperLeftCorner.X + offset,
                        y * tileDimensions.Height + levelRect.UpperLeftCorner.Y + offset);
                rectf tileRect(tilePos, tileDimensions);
                Tile* tile = new Tile;
                tile->graph = graph;
                tile->meshMan = meshMan;
                tile->tileRect = tileRect;
                tile->surface = surface;
                tile->pathMinZ = pathMinZ;
                tile->pathMaxZ = pathMaxZ;
                tile->skyCutZ = skyCutZ;
                tile->refresh();
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

        std::size_t result = y*numTilesX + x;

        if (result >= tileArray.size())
            throw std::logic_error("tileIndex out of bounds.");

        return result;
    }

}}  // namespace Glue
