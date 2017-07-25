#pragma once

namespace irr { namespace scene {
    class IGeometryCreator;
}}

namespace Glue {

class DisplayShapes
{
private:

    irr::scene::IGeometryCreator* geometry;

public:
    DisplayShapes(irr::scene::IGeometryCreator* geometry);

    IMesh* none(GameObjStyle* style) const;
    IMesh* ball(GameObjStyle* style) const;
    IMesh* box(GameObjStyle* style) const;
    IMesh* cyl(GameObjStyle* style) const;
    IMesh* cylX(GameObjStyle* style) const;
    IMesh* cylZ(GameObjStyle* style) const;
    IMesh* cone(GameObjStyle* style) const;
    IMesh* coneX(GameObjStyle* style) const;
    IMesh* coneZ(GameObjStyle* style) const;
    IMesh* hills(GameObjStyle* style) const;
    IMesh* plane(GameObjStyle* style) const;
    IMesh* cloth(GameObjStyle* style) const;
    IMesh* mesh(GameObjStyle* style) const;
    IMesh* skybox(GameObjStyle* style) const;
};

}
