#include "Glue/Avatar/Component.hpp"

namespace Glue { namespace Avatar {

    class Component::Impl
    {
    };

    Component::Component()
    {
    }

    Component::~Component()
    {
    }


    void Component::attachControl(Node* node)
    {

    }

    void Component::beforePhysics(TimeInfo const&)
    {

    }

}}

/*
method(module,
    Component := Object clone lexicalDo(

        module := module

        events ::= nil
        keyInputs ::= nil
        playerAttr ::= nil

        init := method(
            setKeyInputs(module KeyInputs clone)
        )

        attachControl := method(node,
            // TODO:  Remove old player attr from old node if they exist.
            setPlayerAttr(module NodeAttribute clone)
            node addAttribute(playerAttr)
        )

        beforePhysics := method(
            if (playerAttr != nil,
                keyInputs update(playerAttr, events)
            )
        )
    )
)
*/
