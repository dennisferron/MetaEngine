#include "Glue/Styles/GameObjStyle.hpp"

namespace Glue {

    GameObjStyleBase::GameObjStyleBase(ObjShapes shape)
    : GameObjStyleBase(shape, shape)
{
}

    GameObjStyleBase::GameObjStyleBase(ObjShapes dispShape, ObjShapes physShape)
    :   dispShape(dispShape),
        physShape(physShape),
        gameObjType(GameObjTypes::rigid)
{
    // Location
    x = 0;
    y = 0;
    z = 0;


    // Velocity
    xv = 0;
    yv = 0;
    zv = 0;

    // Physical properties
    mass = 1;
    friction = 0.5;
    //restitution = empty;
    //margin = empty;

    // Set to true to make the physics body take its position
    // from the irrilicht node.  Collisions from physics objects
    // won't affect it but it will affect other objects.
    isKinematic = false;

    // Set to true to cause the object never to deactivate.
    // This is important if the object might be moved by means
    // other than something colliding with it.  (Note: isKinematic also disables deactivation.)
    disableDeactivation = false;

    gravityType = GravityType::default_;
    //gravityX := nil
    //gravityY := nil
    //gravityZ := nil

    // 1 gives no damping and 0 is fully damped.
    linDamping = 0;
    angDamping = 0;

    // Collision properties
    ShortBitMask collisionGroup = DefaultCollisionGroup; //DefaultFilter
    ShortBitMask collisionMask = DefaultCollisionMask;
    CollisionResponseTags collisionResponseTag = CollisionResponseTags::none;


    // Dimensions - sphere/cylinder/cone
    radius = 1;
    length = 1;
    closeEnds = true;  // for cylinder

    // Dimensions - box
    xSize = 1;
    ySize = 1;
    zSize = 1;

    // Appearance properties
    color = SColor(255, 255, 255, 255);

    // Set to a file name to load the texture.
    textureFile = "";

    // Change the way TCoords wrap for e.g. cylinder or cone
    alternateTextureWrap = false;

    // New method of changing texture wrap:  pass a block to execute
    //onTextureWrap ::= nil

    // Set one or the other of the following two rotation styles but not both.
    // Yaw, Roll, Pitch are used iff axisX==axisY==axisZ==0.

    // Rotation by axis and angle (better for first person view? might be useful for space ship game -?)
    axisX = 0;
    axisY = 0;
    axisZ = 0;
    angle = 0;

    // Rotation by yaw, pitch, roll (better if your frame of reference is outside the object -?)
    yaw = 0;
    pitch = 0;
    roll = 0;

    // Linear factor lets you constrain the object to 0 in X, Y or Z to keep the object on a 2D plane
    // 1 == normal, 0 == force 0
    linFactorX = 1;
    linFactorY = 1;
    linFactorZ = 1;

    // Angular factor lets you disable certain rotations of the object (useful for 2D game)
    angFactorX = 1;
    angFactorY = 1;
    angFactorZ = 1;

    // Scale the bullet and irrlicht shapes
    dispScaleX = 1;
    dispScaleY = 1;
    dispScaleZ = 1;
    physScaleX = 1;
    physScaleY = 1;
    physScaleZ = 1;

    gameObjType = GameObjTypes::rigid;

    wireframe = false;

    // If set to an Irrlicht mesh, display shape will use this mesh instead of the dispshape name.
    // (And if physShape name is "mesh", then physShape will be built from this mesh object.)
    // I will probably remove this field in a future version of the engine, because
    // this field breaks the property of GameObjStyleBases that they describe 3D objects rather
    // than contain pieces of them (and that propery is desirable e.g. for things like
    // serialization of game objects).
    mesh = nullptr;
}

// Set x,y,z all at once
GameObjStyleBase& GameObjStyleBase::setPos(Scalar x, Scalar y, Scalar z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}

std::tuple<Scalar, Scalar, Scalar> GameObjStyleBase::getPos() const
{
    return std::make_tuple(x, y, z);
}

// Set xv, yv, zv all at once
GameObjStyleBase& GameObjStyleBase::setVel(Scalar xv, Scalar yv, Scalar zv)
{
    this->xv = xv;
    this->yv = yv;
    this->zv = zv;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setGravityType(GravityType gravityType)
{
    this->gravityType = gravityType;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setGravity(Scalar x, Scalar y, Scalar z)
{
    gravityType = GravityType::custom;
    gravityX = x;
    gravityY = y;
    gravityZ = z;
    return *this;
}


GameObjStyleBase& GameObjStyleBase::setDamping(Scalar lin, Scalar ang)
{
    linDamping = lin;
    angDamping = ang;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setSize(Scalar sz)
{
    this->xSize = sz;
    this->ySize = sz;
    this->zSize = sz;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setSize(Scalar xSize, Scalar ySize, Scalar zSize)
{
    this->xSize = xSize;
    this->ySize = ySize;
    this->zSize = zSize;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setShape(ObjShapes s)
{
    physShape = s;
    dispShape = s;
    return *this;
}

// Note:  This method puts alpha last as opposed to SColor which has it first.
GameObjStyleBase& GameObjStyleBase::setColor(IntColor r, IntColor g, IntColor b, IntColor a)
{
    color = SColor(a, r, g, b);
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setColor(SColor c)
{
    color = c;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setTextureFile(std::string value)
{
    textureFile = value;
    textureMap[TextureKeys::primary] = value;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setAxis(Scalar x, Scalar y, Scalar z)
{
    axisX = x;
    axisY = y;
    axisZ = z;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setLinearFactor(Scalar x, Scalar y, Scalar z)
{
    linFactorX = x;
    linFactorY = y;
    linFactorZ = z;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setAngularFactor(Scalar x, Scalar y, Scalar z)
{
    angFactorX = x;
    angFactorY = y;
    angFactorZ = z;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setDispScale(Scalar x, Scalar y, Scalar z)
{
    dispScaleX = x;
    dispScaleY = y;
    dispScaleZ = z;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setPhysScale(Scalar x, Scalar y, Scalar z)
{
    physScaleX = x;
    physScaleY = y;
    physScaleZ = z;
    return *this;
}

GameObjStyleBase& GameObjStyleBase::setScale(Scalar x, Scalar y, Scalar z)
{
    setDispScale(x, y, z);
    setPhysScale(x, y, z);
    return *this;
}

bool GameObjStyleBase::isMouseDraggable() const
{
    return mesh != 0;
}

}