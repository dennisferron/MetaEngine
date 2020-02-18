#pragma once

#include "Glue/Styles/GameObjStyle.hpp"
#include "Glue/Styles/LinkStyle.hpp"
#include "Glue/Styles/ConstraintStyle.hpp"
#include "ISceneNode.h"


#include <vector>
#include <string>
#include <memory>
#include <variant>

namespace Glue
{
    namespace Avatar
    {
        class IAvatarComponent;
        class IAvatarAttribute;
        class IAvatarCamera;
    }

    namespace Irrlicht
    {
        class IIrrlichtComponent;
        class IIrrlichtAttribute;
    }

    namespace Bullet
    {
        class IBulletAttribute;
        class IBulletComponent;
    }

    using NodeAttribute = std::variant<
            Avatar::IAvatarAttribute*,
            Irrlicht::IIrrlichtAttribute*,
            Bullet::IBulletAttribute*>;

    using GraphComponent = std::variant<
            Avatar::IAvatarComponent*,
            Irrlicht::IIrrlichtComponent*,
            Bullet::IBulletComponent*>;

	class ILink
    {
    };

	class IStructure
    {
    };

	// TODO:  If all of the components and attributes use interfaces,
	// maybe the Model doesn't need have interfaces.
	//
	// The higher level objects should forward declare the lower level ones
	// that they use, so that code which uses only a subset of the components
	// doesn't need to reference anything from the components or attributes not used.
	
	class INode
	{
	public:
	    virtual ~INode() {}
		virtual NodeStyle const& get_style() const = 0;
		virtual void addAttribute(NodeAttribute attr) = 0;
	};
	
    class IGraph
    {
    public:

        virtual ~IGraph() {}
        virtual INode* addNode(NodeStyle const& style) = 0;
        virtual ILink* addLink(LinkStyle const& style, INode* fromNode, INode* toNode) = 0;
        virtual void removeLink(ILink* link) const = 0;
        virtual void playSound(std::string const& file) = 0;
        virtual void createCamera(INode* lockObj) = 0;
        virtual INode* nodeToGameObj(irr::scene::ISceneNode* node) const = 0;
        virtual void removeObj(INode* obj) = 0;
        virtual IStructure* addStructure(IStructure* structure, IStructure* leftHandSide) = 0;
    };

}
