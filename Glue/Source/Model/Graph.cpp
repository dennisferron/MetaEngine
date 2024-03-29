#include "Glue/Model/Graph.hpp"

#include "Glue/Bullet/BulletComponent.hpp"
#include "Glue/Irrlicht/IrrlichtComponent.hpp"

#include "Glue/Model/Node.hpp"
#include "Glue/Model/Link.hpp"

namespace Glue
{
    Graph::Graph()
    {
        // I assume the code below was moved...somewhere?

        // TODO:  Decouple Time proto from irrComponent
        //setTime(Time clone setDeviceTimer(irrComp deviceTimer))

        //setPlayer(Player clone create(self))

        //setMenu(nil)

        // Have to add engine to irr component before keyboard and mouse can be inited
        // (see todo below)
        //irrComp setEngine(self)

        // TODO:  Refactor this, currently Keyboard knows too much about Engine
        //setKeyboard(irrComp keyboard)
        //setMouse(irrComp keyboard)
    }


    Graph::~Graph()
    {
    }

    void Graph::addComponent(IGraphObserver* component)
    {
        // TODO: Run interactions before push_back
        components.push_back(component);
    }

    void Graph::addShape(Shape* shape)
    {
        shapes.push_back(shape);

        for (auto c : components)
        {
            c->addShape(shape);
        }
    }

    void Graph::addNode(Node* node)
    {
        nodes.push_back(node);

        for (auto c : components)
        {
            c->addNode(node);
        }
    }

    void Graph::addLink(Link* link)
    {
        links.push_back(link);

        for (auto c : components)
        {
            c->addLink(link);
        }
    }

/*
    void Graph::removeLink(Link* link) const
    {
        // TODO:  Remove from links vector
        // TODO:  Notify components to remove link attributes
    }

// Deprecated?  Not sure...
    void Graph::playSound(std::string const& file)
    {
//    if(sound != nil,
//        sound play2D(file, false, false, false, ESM_AUTO_DETECT, false)
//    )
    }

    void Graph::createCamera(Node* lockObj)
    {
        // TODO:  Check that this is done using the interaction now?
        //Graph createCamera := method(lockObj, irrComp createCamera(lockObj))
    }
*/

/*
    void Graph::removeConstraint(IConstraint* constraint)
    {
        throw "TODO:  should this be in bullet component?";
        //bltComp->removeConstraint(constraint);
    }

    void Graph::addConstraint(ConstraintStyle const& style, Node* objA, Node* objB)
    {
        throw "TODO:  should this be in bullet component?";
        //bltComp->addConstraint(style, objA, objB);
    }
*/

/*
    Node* Graph::nodeToGameObj(irr::scene::ISceneNode* node) const
    {
        throw "TODO:  should this be in irrlicht component?";
        //return irrComp nodeToGameObj(node);
    }

    void Graph::removeObj(Node* obj)
    {
        throw "TODO:  should this be in irrlicht component?";
        //objList.remove(obj);
        //irrComp.removeObj(obj);
    }
*/

    /*
    Structure* Graph::addStructure(Structure* structure, Structure* leftHandSide)
    {
        // TODO: Implement structure
        throw "Not implemented";

        if (structure style == "root") then(
            return addStructure(structure attachments at(0))
        ) elseif (
            structure style == nil and structure embedObj == nil
        ) then (
            Exception raise("style is nil!")
        ) elseif (
            // This is a nested structure object in the place of a constraint or object style.
            structure style type == "Structure"
        ) then(
            result := addStructure(structure style, leftHandSide)       // add nested structure as a unit
            structure attachments foreach(a, addStructure(a, result))  // connect attachments that are outside the nested structure
            return result

        ) elseif(
            // A constraint connects the left hand side with all its right hand side attachments
            structure style hasProto(ConstraintStyle)
        ) then(
            // TODO: Disable this check when constraint style is attached to world on one end.
            if (leftHandSide == nil, Exception raise("Nothing to connect constraint to on left hand side."))
            structure attachments foreach(a,
                c := addConstraint(
                    structure style, leftHandSide, addStructure(a)
                )
            )
            return structure

        ) else(
            // An object style becomes the left hand side for its attachments and returns as a right hand side.

            // Handle existing Nodes embedded in structures, else use style.
            if( structure embedObj != nil,
                obj := structure embedObj
            ,
                obj := addObj(structure style)
            )

            if (obj == nil, Exception raise("Failed to add object in structure."))

            // When the left hand side is an object and not a constraint, add it as a child object (but only if it is kinematic).
            // (If the left hand side is a constraint, this object gets added after the method returns.)
            if (leftHandSide != nil and leftHandSide style hasProto(GameObjStyle) and obj style isKinematic,
                leftHandSide addChild(obj))

            structure attachments foreach(a, addStructure(a, obj))
            return obj
        )
    }
    */
}
