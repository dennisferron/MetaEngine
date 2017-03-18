#pragma once

#include <vector>
#include <string>

namespace MetaEngine {

class RootModule;

}

namespace MetaEngine { namespace Styles {

class GameObjStyle;  // Todo: rename to NodeStyle
using NodeStyle = GameObjStyle;
class LinkStyle;    // Todo:  investigate if can merge with ConstraintStyle
class ConstraintStyle;

}}

namespace MetaEngine { namespace Model {

class Component;
class Domain;
class Interaction;
class Node;
class Link;

class Graph
{
private:
    RootModule* module;

    std::vector<Component*> components;
	Domain* domain;

    // possible interactions shared among all instances
    std::vector<Interaction*> possibleInteractions;

    Node* addNode(NodeStyle const& style);
    Link* addLink(LinkStyle const& style, Node* fromNode, Node* toNode);
    void removeLink(Link* link) const;
    void registerInteraction(Interaction* interaction);
    void addComponent(Component* newComp, Interaction* expectedInteraction);
    void init();

    // Deprecated?  Not sure...
    void playSound(std::string const& file);
    void createCamera := method(lockObj, irrComp createCamera(lockObj))

    ~Graph();

    void removeConstraint(Constraint* constraint);
    void addConstraint := method(ConstraintStyle const& style, Node* objA, Node* objB);


Graph nodeToGameObj := method(node, irrComp nodeToGameObj(node))

Graph removeObj := method(obj,
    objList remove(obj)
    irrComp removeObj(obj)
)

Graph addStructure := method(structure, leftHandSide,

    //writeln("structure style ", structure style)

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
)

return Graph

}}


