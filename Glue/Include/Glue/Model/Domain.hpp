#pragma once

#include "Glue/Model/Object.hpp"
#include "Glue/Model/Interaction.hpp"

#include <string>
#include <map>
#include <vector>
#include <set>

namespace Glue {

class Domain
{
private:
    std::map<std::string, std::set<Object*>> activeObjects;
    std::vector<InteractionInstance> activeInteractions;

    // Instead of 1:1 relationship site:domain, just make sites derive from Domain.
    //Site* site;

public:

    Domain()
    {
    }

    // merge usages:
    // Link setGraph    domain.merge("component", graph->domain, "component");
    // Link setToNode   domain.merge("toNode", toNode->domain, "node");
    // Link setFromNode domain.merge("fromNode", fromNode->domain, "node");
    Domain& merge(std::string targetSubdomain, Domain const& sourceDomain, std::string sourceSubdomain)
    {
        auto iter = sourceDomain.activeObjects.find(sourceSubdomain);

        if (iter != sourceDomain.activeObjects.end())
        {
            for (auto const& obj : iter->second)
            {
                addObject(targetSubdomain, obj);
            }
        }
        else
        {
            throw std::logic_error("Missing source subdomain merging target " + targetSubdomain + " with source " + sourceSubdomain);
        }
    }

    Domain& addObject(std::string subdomain, Object* newObj)
    {
        activeObjects[subdomain].insert(newObj);
        return *this;

//            // Activate new interactions if the interaction is triggerred.
//            activeInteractions appendSeq(
//                site possibleInteractions select(i,
//                    if(i hasOneTrigger(subdomain, newObj) and i isFullyTriggeredBy(activeObjects) ,
//                        i clone setSite(site) with(activeObjects)
//                    )
//                )
//            )
//
//            self
//        )
    }

    //void checkInteraction(Interaction* expectedInteraction, Domain* subdomain, Object* newObj);
    template <typename T>
    Object* findObject(std::string subdomain)
    {
        throw "Not implemented";

        auto iter = activeObjects.find(subdomain);

        if (iter != activeObjects.end())
        {
            for (auto const& obj : iter->second)
            {
                // "if obj is T, return obj
            }
        }

        return nullptr;
    }
};

}
