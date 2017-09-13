// Can't really get this one up and running until Referent is figured out...

#pragma once

#include <string>
#include <vector>

namespace Glue {

class Domain;
class Referent;

class Interactor
{
    virtual ~Interactor() = 0;
};

// Proto for interactions, provides the setTrigger method for clones to
// use to call out the combination of attributes which trigger them.
// When the triggering combination of attributes is added to a GameObject clone,
// a clone of the interaction is made, the trigger slots are set with the
// attributes that triggerred it, and then the activate method is called.
class Interaction
{
private:

    std::vector<Domain*> subdomains;
    Domain* site;
    Referent* referent;

public:

    // I think the subdomains (keys) correspond to slot names.
    std::map<Domain*, Referent*> mapSubdomains();

    bool hasOneTrigger(Domain* subdomain, Object* newObj) const;
    bool isFullyTriggeredBy(std::vector<Object*> const& activeObjects) const;

    std::vector<Object*> getTriggers();

    Interaction(std::vector<Object*> const& activeObjects);
};

}
