#include "Glue/Factory/NodeFactory.hpp"
#include "Glue/Animators/KinematicAnimator.hpp"
#include "Glue/Animators/PhysicsAnimator.hpp"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

namespace Glue
{
    NodeFactory::NodeFactory(btDynamicsWorld* dynamicsWorld, irr::scene::ISceneManager* smgr)
        : dynamicsWorld(dynamicsWorld), smgr(smgr)
    {
    }

    Node* NodeFactory::create_node(NodeStyle const& style, Shape* shape)
    {
        auto physShape = shape->physShape;

        if (physShape == nullptr)
            throw std::logic_error("physShape cannot be null");

        Scalar mass = style.isKinematic ? 0 : style.mass;

        auto localInertia = btVector3(0, 0, 0);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        if (mass != 0)
            physShape->calculateLocalInertia(style.mass, localInertia);

        // Location
        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(btVector3(style.x, style.y, style.z));

        btQuaternion rot;

        if (style.axisX == 0 && style.axisY == 0 && style.axisZ == 0)
            rot = btQuaternion(style.yaw, style.pitch, style.roll);
        else
            rot = btQuaternion(
                    btVector3(style.axisX, style.axisY, style.axisZ),
                    style.angle);

        startTransform.setRotation(rot);

        // TODO: does this need to be moved to ShapeFactory??
        // This is done here rather than in ShapeBuilder because although bullet scales shapes,
        // irrlicht scales nodes, and the irrlicht node is only created here not in ShapeBuilder.
        // Also, some bullet shapes cannot be scaled anyway & have to be scaled here.
        physShape->setLocalScaling(btVector3(style.physScaleX, style.physScaleY, style.physScaleZ));

        MotionStateAnimator* motionState;
        if (style.isKinematic)
            motionState = new KinematicAnimator(startTransform, shape->offset);
        else
            motionState = new PhysicsAnimator(startTransform, shape->offset);

        auto constructionInfo = btRigidBody::btRigidBodyConstructionInfo(
                mass,
                motionState,
                physShape,
                localInertia);
        constructionInfo.m_friction = style.friction;

        btRigidBody* rigidBody =
                addToWorld(style, constructionInfo);

        irr::scene::ISceneNode* sceneNode =
                buildSceneNode(style, shape->dispShape);

        sceneNode->addAnimator(motionState);

        return new Node(rigidBody, sceneNode, motionState);
    }


//    btRigidBody::btRigidBodyConstructionInfo NodeFactory::createConstructionInfo(
//            NodeStyle const& style,
//            btCollisionShape* physShape,
//            btMotionState* motionState) const
//    {
//        if (physShape == nullptr)
//            throw std::logic_error("physShape cannot be null");
//
//        Scalar mass = style.isKinematic ? 0 : style.mass;
//
//        auto localInertia = btVector3(0, 0, 0);
//
//        //rigidbody is dynamic if and only if mass is non zero, otherwise static
//        if (mass != 0)
//            physShape->calculateLocalInertia(style.mass, localInertia);
//
//        // Location
//        btTransform startTransform;
//        startTransform.setIdentity();
//        startTransform.setOrigin(btVector3(style.x, style.y, style.z));
//
//        btQuaternion rot;
//
//        if (style.axisX == 0 && style.axisY == 0 && style.axisZ == 0)
//            rot = btQuaternion(style.yaw, style.pitch, style.roll);
//        else
//            rot = btQuaternion(
//                    btVector3(style.axisX, style.axisY, style.axisZ),
//                    style.angle);
//
//        startTransform.setRotation(rot);
//
//        // This is done here rather than in ShapeBuilder because although bullet scales shapes,
//        // irrlicht scales nodes, and the irrlicht node is only created in not in ShapeBuilder.
//        // Also, some bullet shapes cannot be scaled anyway & have to be scaled here.
//        physShape->setLocalScaling(btVector3(style.physScaleX, style.physScaleY, style.physScaleZ));
//
//        auto rbInfo = btRigidBody::btRigidBodyConstructionInfo(
//                mass,
//                motionState,
//                physShape,
//                localInertia);
//        rbInfo.m_friction = style.friction;
//
//        return rbInfo;
//    }

    btRigidBody* NodeFactory::addToWorld(
            NodeStyle const& style,
            btRigidBody::btRigidBodyConstructionInfo const& rbInfo) const
    {
        auto rigidBody = new btRigidBody(rbInfo);

        if (style.collisionGroup)
            dynamicsWorld->addRigidBody(rigidBody, *style.collisionGroup, style.collisionMask);
        else
            dynamicsWorld->addRigidBody(rigidBody);

        rigidBody->setLinearFactor(btVector3(style.linFactorX, style.linFactorY, style.linFactorZ));
        rigidBody->setAngularFactor(btVector3(style.angFactorX, style.angFactorY, style.angFactorZ));

        rigidBody->setDamping(style.linDamping, style.angDamping);

        // Must set gravity after adding to dynamics world, or it gets overwritten with the default gravity.
        if (style.gravityType == GravityType::none)
            rigidBody->setGravity(btVector3(0,0,0));
        else if (style.gravityType == GravityType::custom)
            rigidBody->setGravity(btVector3(*style.gravityX, *style.gravityY, *style.gravityZ));

        rigidBody->setLinearVelocity(btVector3(style.xv, style.yv, style.zv));

        // Static mesh objects can be kinematic as well as rigid bodies.
        // I think this is safe for softbody too, although a kinematic softbody
        // doesn't really make a lot of sense.
        if (style.isKinematic)
        {
            rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
            rigidBody->setActivationState(DISABLE_DEACTIVATION);
        }

        if (style.disableDeactivation)
        {
            rigidBody->setActivationState(DISABLE_DEACTIVATION);
        }

        // Restitution applies to static mesh objects and to rigid bodies.
        if (style.restitution)
        {
            rigidBody->setRestitution(*style.restitution);
        }

        return rigidBody;
    }

    irr::video::ITexture* NodeFactory::loadTexture(GameObjStyle const& style, std::string const& key) const
    {
        throw "Implement conversion from string to texture keys enum, or change signature of this function.";
        //assets->loadTextureFromFile(style.textureMap[key]);
    }

    // TODO:  Add this to a Scene or World class
//    irr::scene::ISceneNode* NodeFactory::skybox(GameObjStyle const& style) const
//    {
//        return smgr->addSkyBoxSceneNode(
//                loadTexture(style, "up"),
//                loadTexture(style, "down"),
//                loadTexture(style, "left"),
//                loadTexture(style, "right"),
//                loadTexture(style, "front"),
//                loadTexture(style, "back"),
//                nullptr,    // parent
//                0       // id
//        );
//    }

    ISceneNode* NodeFactory::buildSceneNode(NodeStyle const& style, IMesh* mesh) const
    {
        ISceneNode* sceneNode = nullptr;

        if (mesh == nullptr)
            sceneNode == nullptr;
        else
        {
            sceneNode = smgr->addMeshSceneNode(
                    mesh,  // mesh
                    nullptr, // parent
                    0,         // id
                    vector3df(style.x, style.y, -style.z),    // position
                    vector3df(0, 0, 0),    // rotation
                    vector3df(style.dispScaleX, style.dispScaleY, style.dispScaleZ), // scale
                    false  // alsoAddIfMeshPointerZero
            );

            // Debugging - this creates the boxes and arrows
            /*
            sceneNode addChild(
                irr custom OrientationHelperSceneNode new(
                    1.0, // size
                    sceneNode, // parent
                    smgr, // mgr
                    0     // id
                )
            )
            */
        }

        if (sceneNode != nullptr)
        {
            sceneNode->setMaterialFlag(EMF_LIGHTING, true);

            // TODO: Also create material if wire frame
            if (style.textureFile != "")
            {
                ITexture* texture = nullptr; //assets->loadTextureFromFile(style.textureFile);
                sceneNode->setMaterialTexture(0, texture);
                sceneNode->setMaterialType(EMT_SOLID);
                //sceneNode->setMaterialFlag(EMF_LIGHTING, false);
                sceneNode->setMaterialFlag(EMF_LIGHTING, true);

                auto material = sceneNode->getMaterial(0);

                // Does this do any good?
                material.ColorMaterial = 0;

                // TODO:  Add shininess as a style property
                material.Shininess = 50;

                material.SpecularColor = SColor(25, 25, 25, 25);

                // Setting one of these (diffuse maybe?) really takes the depth out of lighting
                // and makes a textured rigid body look dull
                //material set_AmbientColor(SColor tmpWithARGB(255, 255, 255, 255))
                //material set_DiffuseColor(SColor tmpWithARGB(255, 128, 128, 128))
                //material set_EmissiveColor(SColor tmpWithARGB(255, 5, 5, 5))

                // TODO:  Share node creation code among game objects.
                // BUG: won't get called without texture file
                material.Wireframe = style.wireframe;
            }
        }

        return sceneNode;
    }
}
