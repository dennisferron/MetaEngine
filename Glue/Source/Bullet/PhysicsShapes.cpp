#include "Glue/Bullet/PhysicsShapes.hpp"

#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "BulletCollision/CollisionShapes/btConeShape.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "BulletCollision/CollisionShapes/btTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h"
#include "BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h"

#include "SColor.h"

using namespace irr::core;

namespace
{
    bool is_nan(float f)
    {
        throw "Not implemented";
        //return boost::math::isnan(f);
    }
}

namespace Glue::Bullet
{

    btCollisionShape* create_physics_shape(GameObjStyle const& style, irr::scene::IMesh* dispShapeMesh)
    {
        switch (style.physShape)
        {
            case ObjShapes::none:
            {
                return nullptr;
            }
            case ObjShapes::box:
            {
               return new btBoxShape(btVector3(style.xSize / 2, style.ySize / 2, style.zSize / 2));
            }
            case ObjShapes::ball:
            {
                return new btSphereShape(style.radius);
            }
            case ObjShapes::cyl:
            {
                return new btCylinderShape(btVector3(style.radius, style.length/2, style.radius));
            }
            case ObjShapes::cylX:
            {
                return new btCylinderShapeX(btVector3(style.length/2, style.radius, style.radius));
            }
            case ObjShapes::cylZ:
            {
                return new btCylinderShapeZ(btVector3(style.radius, style.radius, style.length/2));
            }
            case ObjShapes::cone:
            {
                return new btConeShape(style.radius, style.length);
            }
            case ObjShapes::coneX:
            {
                return new btConeShapeX(style.radius, style.length);
            }
            case ObjShapes::coneZ:
            {
                return new btConeShapeZ(style.radius, style.length);
            }
            case ObjShapes::plane:
            {
                btVector3 planeNormal(0, 1, 0);
                btScalar planeConstant = style.y;
                return new btStaticPlaneShape(
                        planeNormal,
                        planeConstant);
            }
            case ObjShapes::mesh:
            {
                auto meshBuf = dispShapeMesh->getMeshBuffer(0);  // frame 0

                if (meshBuf->getVertexType() != irr::video::EVT_STANDARD)
                    throw std::runtime_error("The mesh's vertex data not in the standard format.");

                if (meshBuf->getIndexCount() < 3)
                    throw std::runtime_error("Cannot create physshape for mesh, the mesh has no triangles.");

                btIndexedMesh bulletMesh;

                bulletMesh.m_numTriangles = meshBuf->getIndexCount() / 3;

                auto triangleIndexBase = reinterpret_cast<const unsigned char*>(meshBuf->getIndices());
                bulletMesh.m_triangleIndexBase = triangleIndexBase;

                auto vertexBase = reinterpret_cast<const unsigned char*>(meshBuf->getVertices());
                bulletMesh.m_vertexBase = vertexBase;

                auto indexSize = 2; // 16 bits, 2 bytes
                bulletMesh.m_triangleIndexStride = 3 * indexSize;
                bulletMesh.m_numVertices = meshBuf->getVertexCount();
                bulletMesh.m_vertexStride = sizeof(irr::video::S3DVertex);

                // This will be set when the bullet mesh buf is added to the triangle index vertex array object
                //bulletMesh set_m_indexType(PHY_SHORT)

                // This defaults to whatever bullet is built with (floats or doubles).  For Irrlicht I'm sure we want only floats.
                bulletMesh.m_vertexType = PHY_FLOAT;

                // Cant' figure out how to set the indexType properly here, and a comment indicates this constructor is only for backwards compatibility.
                // Best to use the default constructor and addIndexedMesh where you can specify the index type.
                //meshInterface := btTriangleIndexVertexArray new(numTriangles, indices unsafe_ptr_cast, indexStride, numVertices, vertices unsafe_ptr_cast, vertexStride)

                auto meshInterface = new btTriangleIndexVertexArray();
                meshInterface->addIndexedMesh(bulletMesh, PHY_SHORT);

                return new btBvhTriangleMeshShape(meshInterface, true, true);
            }
            case ObjShapes::hills:
            {
                auto xSize = style.xSize / style.xTiles;
                auto zSize = style.zSize / style.zTiles;
                auto xTiles = style.xTiles;
                auto zTiles = style.zTiles;

                // Bullet does not provide a way to scale heightfields on X,Z
                // so we have to scale the final shape instead - by changing the style.
                //style.setPhysScaleX(xSize * style.dispScaleX)
                //style.setPhysScaleZ(zSize * style.dispScaleZ)
                //style.physScaleX = 1;  // TODO: can't modify const style obj
                //style.physScaleZ = 1;

                // However, when using float bullet uses the irrlicht mesh height directly
                // so it doesn't need to be scaled except by the same as the irrlicht obj is scaled
                //style.physScaleY = style.dispScaleY;  // TODO: can't modify const style obj

                auto tileSize = dimension2df(xSize, zSize);
                auto tileCount = dimension2du(xTiles, zTiles);
                auto material = nullptr;
                auto hillHeight = style.ySize;
                auto countHills = dimension2df(style.xHills, style.zHills);
                auto textureRepeatCount = dimension2df(style.xTextureRepeat, style.zTextureRepeat);

                auto heightStickWidth = style.xTiles;
                auto heightStickLength = style.zTiles;

                auto upAxis = 1;  // 0 = X, 1 = Y, 2 = Z

                auto heightDataType = PHY_FLOAT;

                // bullet ignores scale when the heightfield type is float!!
                // (See line 159 in btHeightfieldTerrainShape.cpp)
                // The correct height will be set by getting it from the mesh directly anyway.
                auto heightScale = 0.0;

                // I think this changes which diagonal the quad is split on to make triangles - ?
                auto flipQuadEdges = false;

                auto buf = dispShapeMesh->getMeshBuffer(0);

                auto pos = buf->getPosition(0);
                float minX = pos.X;
                float maxX = pos.X;
                float minY = pos.Y;
                float maxY = pos.Y;
                float minZ = pos.Z;
                float maxZ = pos.Z;

                for(int i=1; i < buf->getVertexCount(); i++)
                {
                    auto pos = buf->getPosition(i);
                    if (pos.X < minX) minX = pos.X;
                    if (pos.Y < minY) minY = pos.Y;
                    if (pos.Z < minZ) minZ = pos.Z;
                    if (pos.X > maxX) maxX = pos.X;
                    if (pos.Y > maxY) maxY = pos.Y;
                    if (pos.Z > maxZ) maxZ = pos.Z;
                }

                // Irrlicht adds 1 more to X and Z tiles so we have to as well.
                xTiles += 1;
                zTiles += 1;

                // Bullet does NOT save the heightfield array!!  So we need to create with new, not tmp.
                float* heightfieldData = new float[xTiles * zTiles];

                for(int i=0; i < buf->getVertexCount(); i++)
                {
                    auto pos = buf->getPosition(i);
                    auto xCell = (xTiles-1) * (pos.X - minX) / (maxX - minX);
                    auto zCell = (zTiles-1) * (pos.Z - minZ) / (maxZ - minZ);

                    if (xCell < 0 || xCell >= xTiles)
                        throw std::runtime_error("xCell out of bounds for heightfield");
                    if (zCell < 0 || zCell >= zTiles)
                        throw std::runtime_error("zCell out of bounds for heightfield");

                    int cellPos = xCell + xTiles * zCell;

                    heightfieldData[cellPos] = pos.Y;
                }

                auto minHeight = minY;
                auto maxHeight = maxY;

                return new btHeightfieldTerrainShape(
                        heightStickWidth,
                        heightStickLength,
                        heightfieldData,
                        heightScale,
                        minHeight,
                        maxHeight,
                        upAxis,
                        heightDataType,
                        flipQuadEdges
                );
            }
            default:
            {
                throw std::logic_error("Unhandled physics shape.");
            }
        }
    }
}
