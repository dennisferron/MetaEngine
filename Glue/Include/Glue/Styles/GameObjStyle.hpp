#pragma once

#include "Glue/Constants.hpp"

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
    struct GameObjStyle
    {
    protected:

        GameObjStyle(ObjShapes shape);
        GameObjStyle(ObjShapes dispShape, ObjShapes physShape);

    public:

        // Display shape
        ObjShapes dispShape;

        // Physical shape
        ObjShapes physShape;

        GameObjTypes gameObjType;

        // Set physical and display shape at once.
        GameObjStyle& setShape(ObjShapes s);

        // Location
        Scalar x;
        Scalar y;
        Scalar z;

        // Set x,y,z all at once
        GameObjStyle& setPos(Scalar x, Scalar y, Scalar z);
        std::tuple<Scalar, Scalar, Scalar> getPos() const;

        // Velocity
        Scalar xv;
        Scalar yv;
        Scalar zv;

        // Set xv, yv, zv all at once
        GameObjStyle& setVel(Scalar xv, Scalar yv, Scalar zv);

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
        GameObjStyle& setGravityType(GravityType gravityType);
        GameObjStyle& setGravity(Scalar x, Scalar y, Scalar z);

        // 1 gives no damping and 0 is fully damped.
        Scalar linDamping;
        Scalar angDamping;
        GameObjStyle& setDamping(Scalar lin, Scalar ang);

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
        GameObjStyle& setSize(Scalar sz);
        GameObjStyle& setSize(Scalar xSize, Scalar ySize, Scalar zSize);

        // Appearance properties
        SColor color;

        // Note:  This method puts alpha last as opposed to SColor which has it first.
        GameObjStyle& setColor(IntColor r, IntColor g, IntColor b, IntColor a = 255);
        GameObjStyle& setColor(SColor c);

        // Map of texture name keys to texture files
        // Generalizes style texture to include more than one in a style,
        // e.g. for things like skybox.
        std::map<TextureKeys, std::string> textureMap;

        // Set to a file name to load the texture.
        std::string textureFile;
        GameObjStyle& setTextureFile(std::string value);

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
        GameObjStyle& setAxis(Scalar x, Scalar y, Scalar z);

        // Rotation by yaw, pitch, roll (better if your frame of reference is outside the object -?)
        Scalar yaw;
        Scalar pitch;
        Scalar roll;

        // Linear factor lets you constrain the object to 0 in X, Y or Z to keep the object on a 2D plane
        // 1 == normal, 0 == force 0
        Scalar linFactorX;
        Scalar linFactorY;
        Scalar linFactorZ;
        GameObjStyle& setLinearFactor(Scalar x, Scalar y, Scalar z);

        // Angular factor lets you disable certain rotations of the object (useful for 2D game)
        Scalar angFactorX;
        Scalar angFactorY;
        Scalar angFactorZ;
        GameObjStyle& setAngularFactor(Scalar x, Scalar y, Scalar z);

        // Scale the bullet and irrlicht shapes
        Scalar dispScaleX;
        Scalar dispScaleY;
        Scalar dispScaleZ;
        Scalar physScaleX;
        Scalar physScaleY;
        Scalar physScaleZ;
        GameObjStyle& setDispScale(Scalar x, Scalar y, Scalar z);
        GameObjStyle& setPhysScale(Scalar x, Scalar y, Scalar z);
        GameObjStyle& setScale(Scalar x, Scalar y, Scalar z);

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

    using NodeStyle = GameObjStyle;
}
