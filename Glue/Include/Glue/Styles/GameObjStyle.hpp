#pragma once

#include "Glue/Constants.hpp"
#include "Glue/ADT/variant_ptr.hpp"

#include "irrlicht.h"

#include <optional>
#include <map>
#include <string>
#include <functional>

namespace Glue {

    using SColor = irr::video::SColor;
    using ITexture = irr::video::ITexture;
    using IMesh = irr::scene::IMesh;

    enum class ObjShapes
    {
        none,
        box,
        ball,
        cyl,
        cylX,
        cylZ,
        cone,
        coneX,
        coneZ,
        skybox,
        plane,
        mesh,
        hills
    };

    enum class GravityType
    {
        none,
        default_,
        custom
    };

    enum class CollisionResponseTags
    {
        none,
        player,
        elevator,
        gearSlot
    };

    enum class TextureKeys
    {
        primary,
        up,
        down,
        left,
        right,
        front,
        back
    };

    enum class GameObjTypes
    {
        rigid,
        static_,
        soft
    };

    struct ObjPos
    {
        Scalar x;
        Scalar y;
        Scalar z;
    };

    // Inspired by cascading style sheets used in websites, this is "CSS for 3d game objects".

    // Style proto for 3d objects.
    // Creates defaults for all possible object properties.
    // No single object uses all of these properties; different combinations
    // will be used determined by what shape it is (which is itself a property).
    // Note:  Instead of prop ::= value, use setProp(value) in derived styles.
    //
    // Example:  myStyle := GameObjStyle clone prependProto(BallStyle) setPos(10, 20, 30) setColor(200, 100, 50)
    //           engine addObj(myStyle)
    //
    struct GameObjStyleBase
    {
    protected:

        GameObjStyleBase();
        GameObjStyleBase(ObjShapes shape);
        GameObjStyleBase(ObjShapes dispShape, ObjShapes physShape);

    public:

        // Display shape
        ObjShapes dispShape;

        // Physical shape
        ObjShapes physShape;

        GameObjTypes gameObjType;

        // Set physical and display shape at once.
        GameObjStyleBase& setShape(ObjShapes s);

        // Location
        Scalar x;
        Scalar y;
        Scalar z;

        // Set x,y,z all at once
        GameObjStyleBase& setPos(Scalar x, Scalar y, Scalar z);
        std::tuple<Scalar, Scalar, Scalar> getPos() const;

        // Velocity
        Scalar xv;
        Scalar yv;
        Scalar zv;

        // Set xv, yv, zv all at once
        GameObjStyleBase& setVel(Scalar xv, Scalar yv, Scalar zv);

        // Physical properties
        Scalar mass;
        Scalar friction;
        std::optional<Scalar> restitution;
        std::optional<Scalar> margin;

        // Set to true to make the physics body take its position
        // from the irrilicht node.  Collisions from physics objects
        // won't affect it but it will affect other objects.
        bool isKinematic;

        // Set to true to cause the object never to deactivate.
        // This is important if the object might be moved by means
        // other than something colliding with it.  (Note: isKinematic also disables deactivation.)
        bool disableDeactivation;

        GravityType gravityType;
        std::optional<Scalar> gravityX;
        std::optional<Scalar> gravityY;
        std::optional<Scalar> gravityZ;
        GameObjStyleBase& setGravityType(GravityType gravityType);
        GameObjStyleBase& setGravity(Scalar x, Scalar y, Scalar z);

        // 1 gives no damping and 0 is fully damped.
        Scalar linDamping;
        Scalar angDamping;
        GameObjStyleBase& setDamping(Scalar lin, Scalar ang);

        static constexpr ShortBitMask DefaultCollisionGroup = ShortBitMask(-1) ^ Constants::CameraFilter;
        static constexpr ShortBitMask DefaultCollisionMask = ShortBitMask(-1);

        // Collision properties
        ShortBitMask collisionGroup;
        ShortBitMask collisionMask;
        CollisionResponseTags collisionResponseTag;

        // Dimensions - sphere/cylinder/cone
        Scalar radius;
        Scalar length;
        bool closeEnds;  // for cylinder

        // Dimensions - box
        Scalar xSize;
        Scalar ySize;
        Scalar zSize;
        GameObjStyleBase& setSize(Scalar sz);
        GameObjStyleBase& setSize(Scalar xSize, Scalar ySize, Scalar zSize);

        // Appearance properties
        SColor color;

        // Note:  This method puts alpha last as opposed to SColor which has it first.
        GameObjStyleBase& setColor(IntColor r, IntColor g, IntColor b, IntColor a = 255);
        GameObjStyleBase& setColor(SColor c);

        // Map of texture name keys to texture files
        // Generalizes style texture to include more than one in a style,
        // e.g. for things like skybox.
        std::map<TextureKeys, std::string> textureMap;

        // Set to a file name to load the texture.
        std::string textureFile;
        GameObjStyleBase& setTextureFile(std::string value);

        // Change the way TCoords wrap for e.g. cylinder or cone
        bool alternateTextureWrap = false;

        // New method of changing texture wrap:  pass a block to execute
        std::function<void(IMesh*)> onTextureWrap;

        // Set one or the other of the following two rotation styles but not both.
        // Yaw, Roll, Pitch are used iff axisX==axisY==axisZ==0.

        // Rotation by axis and angle (better for first person view? might be useful for space ship game -?)
        Scalar axisX;
        Scalar axisY;
        Scalar axisZ;
        Scalar angle;
        GameObjStyleBase& setAxis(Scalar x, Scalar y, Scalar z);

        // Rotation by yaw, pitch, roll (better if your frame of reference is outside the object -?)
        Scalar yaw;
        Scalar pitch;
        Scalar roll;

        // Linear factor lets you constrain the object to 0 in X, Y or Z to keep the object on a 2D plane
        // 1 == normal, 0 == force 0
        Scalar linFactorX;
        Scalar linFactorY;
        Scalar linFactorZ;
        GameObjStyleBase& setLinearFactor(Scalar x, Scalar y, Scalar z);

        // Angular factor lets you disable certain rotations of the object (useful for 2D game)
        Scalar angFactorX;
        Scalar angFactorY;
        Scalar angFactorZ;
        GameObjStyleBase& setAngularFactor(Scalar x, Scalar y, Scalar z);

        // Scale the bullet and irrlicht shapes
        Scalar dispScaleX;
        Scalar dispScaleY;
        Scalar dispScaleZ;
        Scalar physScaleX;
        Scalar physScaleY;
        Scalar physScaleZ;
        GameObjStyleBase& setDispScale(Scalar x, Scalar y, Scalar z);
        GameObjStyleBase& setPhysScale(Scalar x, Scalar y, Scalar z);
        GameObjStyleBase& setScale(Scalar x, Scalar y, Scalar z);

        bool wireframe;

        // Default is an object is draggable iff it's not static
        virtual bool isMouseDraggable() const;

        // If set to an Irrlicht mesh, display shape will use this mesh instead of the dispshape name.
        // (And if physShape name is "mesh", then physShape will be built from this mesh object.)
        // I will probably remove this field in a future version of the engine, because
        // this field breaks the property of GameObjStyles that they describe 3D objects rather
        // than contain pieces of them (and that propery is desirable e.g. for things like
        // serialization of game objects).
        IMesh* mesh;
    };

    namespace GameObjStyles {

        struct NodeStyle_t : GameObjStyleBase
        {
        };

        struct PlaneStyle_t : GameObjStyleBase
        {
            PlaneStyle_t();

            int xTiles;
            int zTiles;
            int xTextureRepeat;
            int zTextureRepeat;
        };

        struct HillStyle_t : GameObjStyleBase
        {
            HillStyle_t();

            int xTiles;
            int zTiles;
            int xHills;
            int zHills;
            int xTextureRepeat;
            int zTextureRepeat;
        };

        struct GeneratorStyle_t;

        constexpr symbol<NodeStyle_t> EmptyStyle{0};
        constexpr symbol<NodeStyle_t> BoxStyle{1};
        constexpr symbol<NodeStyle_t> BallStyle{2};
        constexpr symbol<NodeStyle_t> CylStyle{3};
        constexpr symbol<NodeStyle_t> CylXStyle{4};
        constexpr symbol<NodeStyle_t> CylZStyle{5};
        constexpr symbol<NodeStyle_t> ConeStyle{6};
        constexpr symbol<NodeStyle_t> ConeXStyle{7};
        constexpr symbol<NodeStyle_t> ConeZStyle{8};
        constexpr symbol<NodeStyle_t> SkyboxStyle{9};
        constexpr symbol<HillStyle_t> HillStyle{10};
        constexpr symbol<PlaneStyle_t> PlaneStyle{11};
        constexpr symbol<NodeStyle_t> WallStyle{12};
        constexpr symbol<GeneratorStyle_t> GeneratorStyle{13};
        constexpr symbol<PlaneStyle_t> ClothStyle{14};

    }

    using GameObjStyle = variant_ptr<
            GameObjStyleBase,
            GameObjStyles::NodeStyle_t,
            GameObjStyles::HillStyle_t,
            GameObjStyles::PlaneStyle_t,
            GameObjStyles::GeneratorStyle_t
        >;

    using NodeStyle = GameObjStyle;

    namespace GameObjStyles
    {
        struct GeneratorStyle_t : GameObjStyleBase
        {
            GameObjStyle spawnStyle;

            GeneratorStyle_t()
              : GameObjStyleBase(ObjShapes::none)
            {
                isKinematic = true;
                collisionGroup = 0;  // TODO:  make a group just for generators
                collisionMask = 0;

                spawnStyle->setVel(0, 30, 0);
            }
        };
    }
}
