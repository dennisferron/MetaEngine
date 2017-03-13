// Copyright 2008-2013, 2017 Dennis Ferron

#pragma once

#include "irrlicht.h"
#include "Glue/PossibleVertex.hpp"

#include <map>
#include <vector>
#include <set>

namespace MetaEngine {

class LinkSplitter
{
private:
    irr::scene::IMeshBuffer* oldMeshBuf;
    float zCut;

    std::map<std::pair<int, int>, PsblVertPtr> splitLinksMidpoints;
    std::vector<PsblVertPtr> existingVertices;

    PsblVertPtr splitLink(int oldIndexLeft, int oldIndexRight);

public:

    LinkSplitter(irr::scene::IMeshBuffer* oldMeshBuf_, float zCut_);
    PsblVertPtr processLink(std::vector<PsblVertPtr>& left, std::vector<PsblVertPtr>& right, int a, int b);
    void addConvexShape(std::vector<PsblVertPtr> const& newShape, irr::scene::SMeshBuffer* newMeshBuf, irr::core::vector3df offset);
    void addEdgeLinks(std::vector<PsblVertPtr> const& shape, std::set<std::pair<PsblVertPtr,PsblVertPtr>>& links);
    PsblVertPtr getVert(int oldIndex);
    int compareZ(int oldIndex);
    int compareZ(PsblVertPtr vert);
    std::vector<PsblVertPtr> chopLink(PsblVertPtr left, PsblVertPtr right, int numNewPoints);
    void insertPoints(std::vector<PsblVertPtr>& shape, PsblVertPtr left, PsblVertPtr right, std::vector<PsblVertPtr> const& source);
};


}
