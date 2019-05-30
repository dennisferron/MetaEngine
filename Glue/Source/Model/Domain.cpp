#include "Glue/Model/Domain.hpp"

namespace Glue {

//void Domain::checkInteraction(Interaction* expectedInteraction, Domain* subdomain, Object* newObj)
//{
//    throw "Not implemented";

//        checkInteraction := method(expectedInteraction, subdomain, newObj,
//            //writeln("site possibleInteractions is ", site possibleInteractions)
//            if(site possibleInteractions contains(expectedInteraction),
//                writeln("expectedInteraction is in list")
//            ,
//                writeln("expectedInteraction is not in list of possible interactions!")
//            )
//            if( subdomain == nil,
//                if( expectedInteraction isFullyTriggeredBy(activeObjects),
//                    writeln("interaction should be triggered")
//                ,
//                    writeln("interaction will not be triggered because:")
//                    expectedInteraction clone with(activeObjects)
//                )
//            ,
//                if( hasOneTrigger := expectedInteraction hasOneTrigger(subdomain, newObj) ,
//                    if( expectedInteraction isFullyTriggeredBy(activeObjects),
//                        writeln("interaction should be triggered")
//                    ,
//                        writeln("interaction will not be triggered because:")
//                        expectedInteraction clone with(activeObjects)
//                    )
//                ,
//                    writeln("expectedInteraction is not triggered by ", newObj type, " with protos ", newObj protos select(p, p type))
//                    writeln("because the attribute added does not have any proto among ", expectedInteraction getTriggers)
//                )
//            )
//        )
//}

}

