#include "Model/Domain.hpp"

namespace Glue {

Domain::Domain() :
    site(nullptr)
{
}

Domain& Domain::merge(Domain* targetSubdomain, Domain* sourceDomain, Domain* sourceSubdomain)
{
    if(sourceDomain->activeObjects.hasKey(sourceSubdomain),
                sourceDomain activeObjects at(sourceSubdomain) foreach(obj,
                    self addObject(targetSubdomain, obj)
                )
            ,
                Exception raise("Missing source subdomain merging target " .. targetSubdomain .. " with source " .. sourceSubdomain)
            )
            self
        )
}

Domain& Domain::addObject(Domain* subdomain, Object* newObj, Interaction* expectedInteraction)
{
        addObject := method(subdomain, newObj, expectedInteraction,

            activeObjects hasKey(
                subdomain
            ) ifFalse(
                activeObjects atPut(subdomain, list())
            )

            activeObjects at(subdomain) append(newObj)

            if( expectedInteraction != nil,
                checkInteraction(expectedInteraction, subdomain, newObj)
            )

            // Activate new interactions if the interaction is triggerred.
            activeInteractions appendSeq(
                site possibleInteractions select(i,
                    if(i hasOneTrigger(subdomain, newObj) and i isFullyTriggeredBy(activeObjects) ,
                        i clone setSite(site) with(activeObjects)
                    )
                )
            )

            self
        )
}

void Domain::checkInteraction(Interaction* expectedInteraction, Domain* subdomain, Object* newObj)
{
        checkInteraction := method(expectedInteraction, subdomain, newObj,
            //writeln("site possibleInteractions is ", site possibleInteractions)
            if(site possibleInteractions contains(expectedInteraction),
                writeln("expectedInteraction is in list")
            ,
                writeln("expectedInteraction is not in list of possible interactions!")
            )
            if( subdomain == nil,
                if( expectedInteraction isFullyTriggeredBy(activeObjects),
                    writeln("interaction should be triggered")
                ,
                    writeln("interaction will not be triggered because:")
                    expectedInteraction clone with(activeObjects)
                )
            ,
                if( hasOneTrigger := expectedInteraction hasOneTrigger(subdomain, newObj) ,
                    if( expectedInteraction isFullyTriggeredBy(activeObjects),
                        writeln("interaction should be triggered")
                    ,
                        writeln("interaction will not be triggered because:")
                        expectedInteraction clone with(activeObjects)
                    )
                ,
                    writeln("expectedInteraction is not triggered by ", newObj type, " with protos ", newObj protos select(p, p type))
                    writeln("because the attribute added does not have any proto among ", expectedInteraction getTriggers)
                )
            )
        )
}

Object* Domain::findObject(Domain* subdomain, Type* objProto)
{
        findObject := method(subdomain, objProto,
            activeObjects at(subdomain) foreach(obj,
                if(obj hasProto(objProto), return obj)
            )
            nil
        )
}

}
