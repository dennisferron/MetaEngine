// Can't really get this one up and running until Referent is figured out...

#pragma once

#include <string>
#include <vector>
#include <map>

#include "Glue/Model/Domain.hpp"
#include "Glue/Model/Referent.hpp"

namespace Glue {

    class Domain;

// Proto for interactions, provides the setTrigger method for clones to
// use to call out the combination of attributes which trigger them.
// When the triggering combination of attributes is added to a GameObject clone,
// a clone of the interaction is made, the trigger slots are set with the
// attributes that triggerred it, and then the activate method is called.

// TODO:  Possibly these should be templates so that we'd have:
// possibleInteractions : vector< InteractionRule<Component> >
// activeInteractions : vector< InteractionInstance<Component> >
// _OR_ maybe we don't need 3 different types (ComponentInteraction, NodeInteraction, LinkInteraction)

    class InteractionRule
    {
    private:

        std::vector<std::string> subdomains;
        std::map<std::string, Referent> referent;

    public:

        virtual std::map<std::string, Referent> mapSubdomains() const = 0;

        bool hasOneTrigger(std::string subdomain, Object* newObj) const;
        bool isFullyTriggeredBy(std::vector<Object*> const& activeObjects) const;
    };

    class InteractionInstance
    {
    private:

        std::vector<std::string> subdomains;
        Domain* site;

    public:

        std::map<std::string, Referent*> mapSubdomains();

        virtual void setSite(Domain* site);
        virtual void setSlot(Object* obj) = 0;
    };

}
