// Copyright 2008-2013, 2017 Dennis Ferron

#include "Glue/MeshTools.hpp"
#include "irrlicht.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cassert>
#include <tuple>
using namespace std;
using namespace boost;

using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

namespace Glue {

IMesh* MeshTools::createMeshFromSoftBody(btSoftBody* softBody)
{
	SMeshBuffer* buffer = new SMeshBuffer();
	video::S3DVertex vtx;
	vtx.Color.set(255,255,255,255);

    /* Each soft body contain an array of vertices (nodes/particles_mass)   */
    btSoftBody::tNodeArray&   nodes(softBody->m_nodes);

    // Convert bullet nodes to vertices
    for(int i=0;i<nodes.size();++i)
    {
        const btSoftBody::Node&	n=nodes[i];
        const btVector3 normal=n.m_n;
        const btVector3 pos=n.m_x;

        vtx.Pos.set(pos.getX(), pos.getY(), pos.getZ());
		vtx.Normal.set(normal.getX(), normal.getY(), normal.getZ());

        // TODO: calculate texture coords
        //vtx.TCoords.set(tsx, tsy);

        buffer->Vertices.push_back(vtx);
    }

    // Convert triangles of the softbody to an index list
    for(int i=0;i<softBody->m_faces.size();++i)
    {
        auto	faces = softBody->m_faces;

        btSoftBody::Node*   node_0=faces[i].m_n[0];
        btSoftBody::Node*   node_1=faces[i].m_n[1];
        btSoftBody::Node*   node_2=faces[i].m_n[2];

        const int indices[] =
        {
            int(node_0-&nodes[0]),
            int(node_1-&nodes[0]),
            int(node_2-&nodes[0])
        };

        for(int j=0;j<3;++j)
            buffer->Indices.push_back(indices[j]);
    }

	buffer->recalculateBoundingBox();

	// Default the mesh to stream because most likely we will be updating
	// the vertex positions every frame to deal with softbody movement.
	buffer->setHardwareMappingHint(EHM_STREAM);

	SMesh* mesh = new SMesh();
	mesh->addMeshBuffer(buffer);
	mesh->recalculateBoundingBox();
	buffer->drop();
	return mesh;
}

btSoftBody* MeshTools::createSoftBodyFromMesh(btSoftBodyWorldInfo& worldInfo, IMesh* mesh)
{
	IMeshBuffer* buffer = mesh->getMeshBuffer(0);

	vector<btScalar> vertices;
	for (unsigned int i=0; i < buffer->getVertexCount(); ++i)
	{
	    vector3df p = getBaseVertex(buffer, i).Pos;
	    vertices.push_back(p.X);
	    vertices.push_back(p.Y);
	    vertices.push_back(p.Z);
	}

    vector<int> triangles;
    for (unsigned int i=0; i < buffer->getIndexCount(); ++i)
        triangles.push_back(buffer->getIndices()[i]);

    auto result = btSoftBodyHelpers::CreateFromTriMesh(worldInfo, &vertices[0], &triangles[0], buffer->getIndexCount()/3, false);
    result->m_bUpdateRtCst = true;
    return result;
}

S3DVertex& MeshTools::getBaseVertex(IMeshBuffer* meshBuf, int n)
{
    size_t vertexSize = 0;

    switch (meshBuf->getVertexType())
    {
        case EVT_TANGENTS:
            vertexSize = sizeof(S3DVertexTangents);
            break;
        case EVT_2TCOORDS:
            vertexSize = sizeof(S3DVertex2TCoords);
            break;
        case EVT_STANDARD:
        default:
            vertexSize = sizeof(S3DVertex);
    }

    void* vertPtr = (char*)meshBuf->getVertices() + n * vertexSize;

    // They all inherit from S3DVertex
    return *reinterpret_cast<irr::video::S3DVertex*>(vertPtr);
}


MeshTools::SplitMeshResult MeshTools::splitMeshZ(IMesh* oldMesh, float zCut, float zInsert, bool marginalTrisInLeft, bool marginalTrisInRight)
{
    IMeshBuffer* oldMeshBuf = oldMesh->getMeshBuffer(0);
    u16* oldInd = oldMeshBuf->getIndices();
	SMeshBuffer* leftMeshBuf = new SMeshBuffer();
	SMeshBuffer* rightMeshBuf = new SMeshBuffer();
    LinkSplitter linkSplitter(oldMeshBuf, zCut);

    vector3df const offset(0,0, zInsert);

    set<pair<PsblVertPtr, PsblVertPtr>> leftEdgeLinks;
    set<pair<PsblVertPtr, PsblVertPtr>> rightEdgeLinks;

    for (u32 i=0; i < oldMeshBuf->getIndexCount(); i += 3)
    {
        // Calling these shapes instead of triangles because they could be triangle or a quad after slice,
        // (it could also be a degenerate case of a line or a point - those will be discarded by addConvexShape)
        vector<PsblVertPtr> leftShape;
        vector<PsblVertPtr> rightShape;

        int a = oldInd[i];
        int b = oldInd[i+1];
        int c = oldInd[i+2];

        PsblVertPtr mid1;
        PsblVertPtr mid2;
        PsblVertPtr mid3;

        // Don't create a copy just for a triangle that is just kissing the edge.  Leave it in the background.
        if (linkSplitter.compareZ(a)==0 && linkSplitter.compareZ(b)==0 && linkSplitter.compareZ(c)==0)
        {
            if (marginalTrisInLeft)
            {
                leftShape.push_back(linkSplitter.getVert(a));
                leftShape.push_back(linkSplitter.getVert(b));
                leftShape.push_back(linkSplitter.getVert(c));
            }

            if (marginalTrisInRight)
            {
                rightShape.push_back(linkSplitter.getVert(a));
                rightShape.push_back(linkSplitter.getVert(b));
                rightShape.push_back(linkSplitter.getVert(c));
            }
        }
        else
        {
            // This is something I had to think hard about so I'm writing this comment so I don't
            // have to think it through again or forget it:
            //
            // Both the left shape and the right shape, and both the triangle and the quad, "magically"
            // come out with correct winding order when the triangle is split.  Here's why:
            //  Let the original triangle vertices be A-B-C.
            //  Let the split midpoints be AB' and CA' as A-B is split and C-A are split respectively.
            // The shapes (ignore which shape is left or right, call them P and Q instead)
            // will be filled in the following order:
            //
            //  round       P   Q       Comment
            //  1           A   -       A is not in Q at all
            //  1 cont.     AB' AB'     AB' replaces B in P
            //  2           -   B       B proper is in Q and not in P
            //  2 cont.     -   -       Link B-C is not split
            //  3           -   C       C proper is in Q and not in P
            //  3 cont.     CA' CA'     CA' replaces C in P
            //
            // Now, read the columns P and Q vertically top to bottom to see the resultant vertex order.
            // The triangle P is trivially still the correct winding order; it is just a smaller triangle now.
            // The new quad Q retains the old triangle's winding order property for the following reason:
            //  As you wrapped around a full circle in old triangle A-B-C you would have traversed C-A then A-B.
            //      The link C-A has been cut and vertex CA' inserted.
            //      The link A-B has been cut and vertex AB' inserted.
            //  If you traverse the new shape starting from the _middle_ you follow the following path:
            //      B-C     C-CA'   CA'-AB'    AB'-B    B-C (again)
            //  Compare to old triangle:
            //      B-C          C-A        A-B         B-C (again)
            //  Even though vertex A has been cut off and replaced with two vertices, the two
            //  new vertices lie along the path that the old links took and are in the new shape in the right order.

            mid1 = linkSplitter.processLink(leftShape, rightShape, a, b);
            mid2 = linkSplitter.processLink(leftShape, rightShape, b, c);
            mid3 = linkSplitter.processLink(leftShape, rightShape, c, a);
        }

        // If a triangle was split then two of those three midpoints are inhabited by a vertex.
        // We want to get them both in mid1 and mid2 AND we need them in correct order.
        PsblVertPtr cut1 = (mid1 && mid2)? mid1 : mid2;
        PsblVertPtr cut2 = (mid2 && mid3)? mid3 : mid2;

        if (cut1 && cut2)
        {
            vector<PsblVertPtr> chain = linkSplitter.chopLink(cut1, cut2, 1);
            linkSplitter.insertPoints(leftShape, cut1, cut2, chain);
            linkSplitter.insertPoints(rightShape, cut1, cut2, chain);
        }

        linkSplitter.addConvexShape(leftShape, leftMeshBuf,   -offset/2);
        linkSplitter.addConvexShape(rightShape, rightMeshBuf,  offset/2);

        // Add any edges of the left shape that lie along the border.
        linkSplitter.addEdgeLinks(leftShape, leftEdgeLinks);

        // Right side polys that share a border with left side ones will have
        // opposite winding order.  In order for set_intersection to consider them
        // as matches, we'll store the right side links in reversed order.
        std::reverse(rightShape.begin(), rightShape.end());
        linkSplitter.addEdgeLinks(rightShape, rightEdgeLinks);
    }

	SMesh* leftMesh = new SMesh();
	leftMeshBuf->recalculateBoundingBox();
	leftMeshBuf->setHardwareMappingHint(EHM_STATIC);
    leftMesh->addMeshBuffer(leftMeshBuf);
	leftMesh->recalculateBoundingBox();
	leftMeshBuf->drop();  // we drop the buf, mesh obj has it now

	SMesh* rightMesh = new SMesh();
	rightMeshBuf->recalculateBoundingBox();
	rightMeshBuf->setHardwareMappingHint(EHM_STATIC);
    rightMesh->addMeshBuffer(rightMeshBuf);
	rightMesh->recalculateBoundingBox();
	rightMeshBuf->drop();  // we drop the buf, mesh obj has it now

    SMesh* middleMesh = NULL;
    if (zInsert > 0)
    {
        set<pair<PsblVertPtr,PsblVertPtr>> result;
        std::set_intersection(
            leftEdgeLinks.begin(), leftEdgeLinks.end(),
            rightEdgeLinks.begin(), rightEdgeLinks.end(),
            std::inserter(result, result.begin())
        );

        size_t debugsize = result.size();

        if (result.size() > 0)
        {
            SMeshBuffer* middleMeshBuf = new SMeshBuffer();

            vector<PsblVertPtr> shape(4);
            for (auto it=result.begin(); it!=result.end(); ++it)
            {
                shape[0] = it->second;
                shape[1] = it->first;
                shape[2] = it->first->duplicate(offset);
                shape[3] = it->second->duplicate(offset);
                linkSplitter.addConvexShape(shape, middleMeshBuf, -offset/2);
            }

            middleMesh = new SMesh();
            middleMeshBuf->recalculateBoundingBox();
            middleMeshBuf->setHardwareMappingHint(EHM_STATIC);
            middleMesh->addMeshBuffer(middleMeshBuf);
            middleMesh->recalculateBoundingBox();
            middleMeshBuf->drop();  // we drop the buf, mesh obj has it now
        }
    }

	return SplitMeshResult {leftMesh, middleMesh, rightMesh};
}


bool MeshTools::compareMeshBuffers(IMeshBuffer* oldMesh, IMeshBuffer* newMesh)
{
    if (oldMesh->getVertexCount() != newMesh->getVertexCount())
    {
        cout << "unequal vertex counts" << std::endl;
        return false;
    }

    if (oldMesh->getIndexCount() != newMesh->getIndexCount())
    {
        cout << "unequal index counts" << endl;
        return false;
    }

    cout << "Checking for duplicate vertexes in " << oldMesh->getVertexCount() << " vertices." << endl;

    // To handle duplicates we'll map instances of duplicates onto their first occurrence

    vector<int> newToNew(newMesh->getVertexCount());
    for (u32 i=0; i < newToNew.size(); ++i)
        newToNew[i] = i;

    vector<int> oldToOld(oldMesh->getVertexCount());
    for (u32 i=0; i < oldToOld.size(); ++i)
        oldToOld[i] = i;

    for (u32 o=0; o < oldMesh->getVertexCount(); ++o)
    {
        cout << "\t" << o;
        auto const& oldVertex = MeshTools::getBaseVertex(oldMesh, o);
        auto const& newVertex = MeshTools::getBaseVertex(newMesh, o);
        for (u32 n=0; n < newMesh->getVertexCount(); ++n)
        {
            if (o==n)
                continue;

            auto const& otherOldVertex = MeshTools::getBaseVertex(oldMesh, n);
            auto const& otherNewVertex = MeshTools::getBaseVertex(newMesh, n);
            if (oldVertex.Pos == otherOldVertex.Pos && oldVertex.TCoords == otherOldVertex.TCoords)
            {
                oldToOld[n] = o;
            }
            if (newVertex.Pos == otherNewVertex.Pos && newVertex.TCoords == otherNewVertex.TCoords)
            {
                newToNew[n] = o;
            }
        }
    }

    // The reason this loop can handle duplicates is because there is no downside to mapping multiple
    // old vertices onto the same new vertex.  Since we find the first match and exit the loop early
    // with the break, we always get the first n of a duplicate never the others.

    vector<int> oldToNew(oldMesh->getVertexCount(), -1);

    cout << "Building vertex equivalence table for " << oldToNew.size() << " vertices." << endl;
    for (u32 o=0; o < oldMesh->getVertexCount(); ++o)
    {
        cout << "\t" << o;
        auto const& oldVertex = MeshTools::getBaseVertex(oldMesh, o);
        for (u32 n=0; n < newMesh->getVertexCount(); ++n)
        {
            auto const& newVertex = MeshTools::getBaseVertex(newMesh, n);
            if (oldVertex.Pos == newVertex.Pos && oldVertex.TCoords == newVertex.TCoords)
            {
                oldToNew[o] = n;
                break;
            }
        }
    }

    cout << "Checking vertex equivalence table" << endl;

    for (u32 o=0; o<oldMesh->getVertexCount(); ++o)
    {
        if (oldToNew[o] == -1)
        {
            cout << "old vertex " << o << " has no equivalent in new mesh." << endl;
            return false;
        }
    }

    cout << "Building triangle lists" << endl;

    auto mktuple = [](int a, int b, int c) { if (c<b) std::swap(c,b); if (b<a) std::swap(b,a); if (b>c) std::swap(b,c); return make_tuple(a, b, c); };
    int triangleCount = oldMesh->getIndexCount() / 3;
    vector<tuple<int, int, int>> oldToNewTris(triangleCount);
    vector<tuple<int, int, int>> newToNewTris(triangleCount);

    u16 const* oldInd = oldMesh->getIndices();
    for (int o=0; o < triangleCount; ++o)
        oldToNewTris[o] = mktuple(oldToNew[oldToOld[oldInd[3*o]]], oldToNew[oldToOld[oldInd[3*o+1]]], oldToNew[oldToOld[oldInd[3*o+2]]] );

    u16 const* newInd = newMesh->getIndices();
    for (int n=0; n < triangleCount; ++n)
        newToNewTris[n] = mktuple(newToNew[newInd[3*n]], newToNew[newInd[3*n+1]], newToNew[newInd[3*n+2]] );

    cout << "Sorting triangle lists" << endl;

    sort(oldToNewTris.begin(), oldToNewTris.end());
    sort(newToNewTris.begin(), newToNewTris.end());

    cout << "Comparing triangle lists" << endl;

    for (int i=0; i<triangleCount; ++i)
    {
        if (oldToNewTris[i] != newToNewTris[i])
        {
            cout << "unequal triangles:" << endl;
            auto oldT = oldToNewTris[i];
            cout << "old: " << get<0>(oldT) << "," << get<1>(oldT) << "," << get<2>(oldT) << endl;
            auto newT = newToNewTris[i];
            cout << "new: " << get<0>(newT) << "," << get<1>(newT) << "," << get<2>(newT) << endl;
            return false;
        }
    }

    return true;
}

IMesh* MeshTools::createMeshFromHeightmap(IImage* image, dimension2du tileSizeInPixels, vector2di tilePosInTiles, bool extraStripsOnEdges)
{
    // Use top corner of image to get bias for centering the Z axis.
    float imageZeroBias = image->getPixel(0,0).getAverage();

    dimension2du imageDimension = image->getDimension();

    // Easier to think of script working in whole tile units, so handle conversion to pixel pos in this method:
    vector2di startAtPixel = tilePosInTiles * vector2di(tileSizeInPixels.Width, tileSizeInPixels.Height);

    // However we're going to invert the image Y axis so that the bottom of the picture will be at 0,0 in world space,
    // and the top of the picture will be at +Y in world space.
    startAtPixel.Y = (imageDimension.Height-1) - startAtPixel.Y;

    // Return nothing if the tile is outside the image, or if the resulting mesh would have only 0 or 1 rows or columns.
    // Doing this check early prevents getting underflow when we clip the tile size to the image dimensions a few statements down.
    if (startAtPixel.X < 0 || startAtPixel.X >= (imageDimension.Width-1) || startAtPixel.Y <= 0 || startAtPixel.Y > (imageDimension.Height-1))
        return NULL;

    // Calculate whether to use tile size or tile size + 1 (for generating overlap)
    // Adding the extra strip amount before clipping to image dimensions prevents overflowing the image edges after clipping.
    dimension2du useTileSize = tileSizeInPixels + (extraStripsOnEdges? dimension2du(1,1) : dimension2du(0,0));

    // Clip the tile size if we're dealing with a "leftover" amount at the edge that's not a whole tile's width or height.
    // Most heightmap implementations require exactly a power of 2 + 1 square dimensions like 257x257, but supporting
    // image sizes that are not whole multiples of tile size is as simple as this one line of code and supporting
    // image sizes that are not square is a nice feature for a platformer game so you can have levels that are longer
    // than they are tall.
    useTileSize.set(min(useTileSize.Width, imageDimension.Width-startAtPixel.X), min(useTileSize.Height, (u32)startAtPixel.Y+1));

	SMeshBuffer* buffer = new SMeshBuffer();

	// Preallocate vertex buffer to the size we know we'll need.
	buffer->Vertices.set_used(useTileSize.Width*useTileSize.Height);

	// Amount of TCoord per unit of x,y in image.
    vector2df tCoordsScale(1.0f / useTileSize.Width, 1.0f / useTileSize.Height);

    // Whether we put y on the outside or x on the outside, doesn't matter, because we are
    // using getIndex() to find where x and y map too.  However, I happen to know I made getIndex
    // put x's together, y in rows, and looping in the same rank order might have better cache performance
    // because it should access the vertices in the same order they are in the array.
    for (u32 y=0; y < useTileSize.Height; ++y)
    {
        for (u32 x=0; x < useTileSize.Width; ++x)
        {
            u32 index = getIndex(useTileSize, x, y);
            S3DVertex& vert = buffer->Vertices[index];

            // No special coloration
            vert.Color = SColor(255,255,255,255);

            // Scale texture to tile.
            vert.TCoords = vector2df(x,y) * tCoordsScale;

            // y axis starts with 0 at image bottom and goes up.
            vector2di pixelPos(
                startAtPixel.X+x,
                startAtPixel.Y-y
            );

            SColor heightColor = image->getPixel(pixelPos.X, pixelPos.Y);
            float thisHeight = imageZeroBias - heightColor.getAverage();

            vert.Pos.set(x, y, thisHeight);

            // I'm only averaging normals along the 4 compass directions.  It's
            // arguable whether diagonals should count; I chose to ignore diagonals.
            // Ignoring diagonals allows me to assume the "run" in rise/run is always
            // just one unit; if you add diagonals here you'll also need to change
            // the slope calculation to use the actual distance instead of assuming 1.
            vector2di offsetsArray[] = {
                vector2di( 1, 0),  //  3 o'clock
                vector2di( 0, 1),  // 12 o'clock
                vector2di(-1, 0),  //  9 o'clock
                vector2di( 0,-1)   //  6 o'clock
            };

            // Calculate the normals of the surrounding slopes.
            // Uses the image, not just the tile patch size, so it will
            // calculate correct normals for vertices on tile edges.
            for (size_t i=-0; i < 4; ++i)
            {
                vector2di offset = vector2di(x,y) + offsetsArray[i];

                // Skip this offset if it's outside the image
                if (offset.X < 0 || offset.Y < 0 || offset.X >= (s32)imageDimension.Width || offset.Y >= (s32)imageDimension.Height)
                    continue;

                vector2di otherPixelPos(
                    startAtPixel.X+x+offset.X,
                    startAtPixel.Y-y-offset.Y
                );
                float otherHeight = 255 - image->getPixel((u32)otherPixelPos.X, (u32)otherPixelPos.Y).getAverage();

                // The code Irrlicht's in terrain scene node does all kinds of complicated
                // business with cross products and such - waaay over complicated.  You don't need
                // all that stuff.  Dude it' s a heightmap: all you need to worray about is
                // rise over run on unit intervals!  Algebra 1 type stuff, y = mx + c

                // Calculate the rise of the line over the run, taking into account the fact
                // that the offset could be in either direction.
                float rise = (offset.X < 0 || offset.Y < 0)? thisHeight - otherHeight : otherHeight - thisHeight;

                // Assuming that run = 1, m = rise / run is just m = rise.
                float m = rise;

                // The the slope of the normal is just the negative of the reciprocal of the line slope.
                float n = -1.0f / rise;

                // The X,Y of the normal vector is just going to be the X and Y of the offset
                // (think about it - obviously the normal of the slope must tilt in the direction of the run)
                // and the Z of the normal vector is just the slope of the normal over that run.
                vector3df normVect(offset.X, offset.Y, n);

                //vert.Normal += normVect;
            }

            //vert.Normal.normalize();
            vert.Normal.set(0,0,-1.0f);
        }
    }

    // Pre-allocate index data to 2*3*Width*Height for triangles.
    // There is actually 1 less square per count of vertices though,
    // for instance if you had 2x2 vertices, you only have 1 square.
    buffer->Indices.set_used(2*3*(useTileSize.Width-1)*(useTileSize.Height-1));

    // Start with 1 and generate all the triangles from their top right corners.
    // Like this (A is top right corner at x,y):
    //
    //              y=1  B---A
    //                   | / |
    //              y=0  C---D
    //                  x=0 x=1
    for (u32 dst=0, x=1; x < useTileSize.Width; ++x)
    {
        for (u32 y=1; y < useTileSize.Height; ++y)
        {
            u32 A = getIndex(useTileSize, x,   y   );
            u32 B = getIndex(useTileSize, x-1, y   );
            u32 C = getIndex(useTileSize, x-1, y-1 );
            u32 D = getIndex(useTileSize, x,   y-1 );

            buffer->Indices[dst++] = C;
            buffer->Indices[dst++] = B;
            buffer->Indices[dst++] = A;

            buffer->Indices[dst++] = D;
            buffer->Indices[dst++] = C;
            buffer->Indices[dst++] = A;
        }
    }

	buffer->recalculateBoundingBox();
	buffer->setHardwareMappingHint(EHM_STATIC);

	SMesh* mesh = new SMesh();
	mesh->addMeshBuffer(buffer);
	mesh->recalculateBoundingBox();
	buffer->drop();
	return mesh;
}

u32 MeshTools::getIndex(dimension2du tileSize, u32 x, u32 y)
{
    // We know what order we generate the vertices in, therefore we
    // know exactly how to
    return y * tileSize.Width + x;
}

bool MeshTools::checkMeshBuffer(IMeshBuffer* meshBuffer, dimension2du tileSize)
{
    bool ok = true;

    if (getIndex(tileSize, tileSize.Width-1, tileSize.Height-1) != meshBuffer->getVertexCount()-1)
    {
        cout << "Wrong number of vertices" << endl;
        return ok = false;
    }

    // Check vertex positions
    for (u32 y=0; y<tileSize.Height; ++y)
    {
        for (u32 x=0; x<tileSize.Width; ++x)
        {
            u32 index = getIndex(tileSize, x, y);

            if (index >= 32768)
            {
                cout << "getIndex " << index << " at pos "<< x << "," << y << " too large for signed int." << endl;
                ok = false;
            }

            if (index >= meshBuffer->getVertexCount())
            {
                cout << "getIndex " << index << " at pos "<< x << "," << y << " larger than vertex buffer count of " << meshBuffer->getVertexCount() << endl;
                return ok=false;
            }

            S3DVertex const& vert = getBaseVertex(meshBuffer, (int)index);

            if (!irr::core::equals(vert.Pos.X, (f32)x))
            {
                cout << "Expected x " << x << " found " << vert.Pos.X << endl;
                ok = false;
            }

            if (!irr::core::equals(vert.Pos.Y, (f32)y))
            {
                cout << "Expected y " << y << " found " << vert.Pos.Y << endl;
                ok = false;
            }
        }
    }

    // Check indices
    if (meshBuffer->getIndexCount() % 3 != 0)
    {
        cout << "Index buffer size not divisible by 3" << endl;
        return ok = false;
    }

    if (meshBuffer->getIndexCount() % 6 != 0)
    {
        cout << "Index buffer size not evenly divisible by 6 (implies it doesn't contain just triangulated squares)" << endl;
        return ok = false;
    }

    for (u32 i=0; i<meshBuffer->getIndexCount(); ++i)
    {
        if (meshBuffer->getIndices()[i] > meshBuffer->getVertexCount())
        {
            cout << "Bad index in index buffer" << endl;
            ok = false;
        }
    }

    for (u32 i=0; i<meshBuffer->getIndexCount()/6; ++i)
    {
        for (u32 j=0; j<2; ++j)
        {
            u16 A = meshBuffer->getIndices()[6*i + 3*j + 0];
            u16 B = meshBuffer->getIndices()[6*i + 3*j + 1];
            u16 C = meshBuffer->getIndices()[6*i + 3*j + 2];

            if (A==B || B==C || C==A)
            {
                cout << "degenerate triangle; one or more vertices the same" << endl;
                ok = false;
            }

            auto& vA = getBaseVertex(meshBuffer, A);
            auto& vB = getBaseVertex(meshBuffer, B);
            auto& vC = getBaseVertex(meshBuffer, C);

            if (abs(vA.Pos.X-vB.Pos.X) > 1.01 || abs(vB.Pos.X-vC.Pos.X) > 1.01 || abs(vC.Pos.X-vA.Pos.X) > 1.01)
            {
                cout << "distance between vertices > 1 in x axis" << endl;
            }

            if (abs(vA.Pos.Y-vB.Pos.Y) > 1.01 || abs(vB.Pos.Y-vC.Pos.Y) > 1.01 || abs(vC.Pos.Y-vA.Pos.Y) > 1.01)
            {
                cout << "distance between vertices > 1 in y axis" << endl;
            }
        }
    }

    return ok;
}

}
