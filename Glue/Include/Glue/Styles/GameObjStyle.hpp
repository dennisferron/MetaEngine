#pragma once

#include "Constants.hpp"

#include "irrlicht.h"

#include <optional>

namespace Glue {

    using SColor = irr::video::SColor;
    using ITexture = irr::video::ITexture;
    using IMesh = irr::scene::IMesh;

    enum class ObjShapes
    {
        none,
        box,
        ball
        cyl,
        cylX,
        cylZ,
        cone,
        coneX,
        coneZ,
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
    }

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

    public:

        // Location
        Scalar x = 0;
        Scalar y = 0;
        Scalar z = 0;

        // Set x,y,z all at once
        GameObjStyle& setPos(Scalar x, Scalar y, Scalar z);

        ObjPos getPos() const;

        // Velocity
        Scalar xv = 0;
        Scalar yv = 0;
        Scalar zv = 0;

        // Set xv, yv, zv all at once
        GameObjStyle& setVel(Scalar xv, Scalar yv, Scalar zv);

        // Physical properties
        Scalar mass = 1;
        Scalar friction = 0.5;
        std::optional<Scalar> restitution;
        std::optional<Scalar> margin;

        // Set to true to make the physics body take its position
        // from the irrilicht node.  Collisions from physics objects
        // won't affect it but it will affect other objects.
        bool isKinematic = false;

        // Set to true to cause the object never to deactivate.
        // This is important if the object might be moved by means
        // other than something colliding with it.  (Note: isKinematic also disables deactivation.)
        bool disableDeactivation = false;

        GravityType gravityType = GravityType::default_;
        std::optional<Scalar> gravityX;
        std::optional<Scalar> gravityY;
        std::optional<Scalar> gravityZ;
        GameObjStyle& setGravity(Scalar x, Scalar y, Scalar z);

        // 1 gives no damping and 0 is fully damped.
        Scalar linDamping = 0.0;
        Scalar angDamping = 0.0;
        GameObjStyle& setDamping(Scalar lin, Scalar ang);

        static constexpr ShortBitMask DefaultCollisionGroup = Bitmask(-1) ^ Constants::CameraFilter;
        static constexpr ShortBitMask DefaultCollisionMask = Constants::AllFilter;

        // Collision properties
        ShortBitMask collisionGroup = DefaultCollisionGroup; //DefaultFilter
        ShortBitmask collisionMask = DefaultCollisionMask;
        CollisionResponseTags collisionResponseTag = CollisionResponseTags::none;

        // Dimensions - sphere/cylinder/cone
        Scalar radius = 1;
        Scalar length = 1;
        bool closeEnds = true;  // for cylinder

        // Dimensions - box
        Scalar xSize = 1;
        Scalar ySize = 1;
        Scalar zSize = 1;

        // Set xSize,ySize,zSize all at once
        GameObjStyle& setSize(Scalar xSize, Scalar ySize, Scalar zSize);

        // Physical shape
        ObjShapes physShape = ObjShapes::box;

        // Display shape
        ObjShapes dispShape ::= ObjShapes::box;

        // Set physical and display shape at once.
        GameObjStyle& setShape(ObjShapes s);

        // Appearance properties
        SColor color = SColor(255, 255, 255, 255);

        // Note:  This method puts alpha last as opposed to SColor which has it first.
        GameObjStyle& setColor(IntColor r, IntColor g, IntColor b, IntColor a = 255);

        // Map of texture name keys to texture files
        // Generalizes style texture to include more than one in a style,
        // e.g. for things like skybox.
        std::map<TextureKeys, ITexture*> textureMap;

        // Set to a file name to load the texture.
        ITexture* texture = nullptr;
        GameObjStyle& setTexture(ITexture* value);

        // Change the way TCoords wrap for e.g. cylinder or cone
        bool alternateTextureWrap = false;

        // New method of changing texture wrap:  pass a block to execute
        std::function<void(IMesh*)> onTextureWrap;

        // Set one or the other of the following two rotation styles but not both.
        // Yaw, Roll, Pitch are used iff axisX==axisY==axisZ==0.

        // Rotation by axis and angle (better for first person view? might be useful for space ship game -?)
        Scalar axisX = 0;
        Scalar axisY = 0;
        Scalar axisZ = 0;
        Scalar angle = 0;
        GameObjStyle& setAxis(Scalar x, Scalar y, Scalar z);

        // Rotation by yaw, pitch, roll (better if your frame of reference is outside the object -?)
        Scalar yaw = 0;
        Scalar pitch = 0;
        Scalar roll = 0;

        // Linear factor lets you constrain the object to 0 in X, Y or Z to keep the object on a 2D plane
        // 1 == normal, 0 == force 0
        Scalar linFactorX = 1;
        Scalar linFactorY = 1;
        Scalar linFactorZ = 1;
        GameObjStyle& setLinearFactor(Scalar x, Scalar y, Scalar z);

        // Angular factor lets you disable certain rotations of the object (useful for 2D game)
        Scalar angFactorX = 1;
        Scalar angFactorY = 1;
        Scalar angFactorZ = 1;
        GameObjStyle& setAngularFactor(Scalar x, Scalar y, Scalar z);

        // Scale the bullet and irrlicht shapes
        Scalar dispScaleX = 1;
        Scalar dispScaleY = 1;
        Scalar dispScaleZ = 1;
        Scalar physScaleX = 1;
        Scalar physScaleY = 1;
        Scalar physScaleZ = 1;
        GameObjStyle& setDispScale(Scalar x, Scalar y, Scalar z);
        GameObjStyle& setPhysScale(Scalar x, Scalar y, Scalar z);
        GameObjStyle& setScale(Scalar x, Scalar y, Scalar z);

        GameObjTypes gameObjType = GameObjTypes::rigid;

        bool wireframe = false;

        // Default is an object is draggable iff it's not static
        bool isMouseDraggable() const;

        // If set to an Irrlicht mesh, display shape will use this mesh instead of the dispshape name.
        // (And if physShape name is "mesh", then physShape will be built from this mesh object.)
        // I will probably remove this field in a future version of the engine, because
        // this field breaks the property of GameObjStyles that they describe 3D objects rather
        // than contain pieces of them (and that propery is desirable e.g. for things like
        // serialization of game objects).
        IMesh mesh = nullptr;
    };
}
