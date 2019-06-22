#pragma once

#include "Glue/Model/Object.hpp"

namespace Glue {

struct Trigger
{
    std::string findProto;
    std::string withSlot;
    bool triggeredBy(Object const* obj) const
    {
        return obj->hasProto(findProto);
    }
};

class Referent
{
private:

    std::vector<Trigger> triggers;

    void setTrigger(std::string slotName, std::string protoName)
    {
        Trigger trigger;
        trigger.withSlot = slotName;
        trigger.findProto = protoName;
    }

    bool hasOneTrigger(Object* obj) const
    {
        for (auto const &t : triggers)
        {
            if (t.triggeredBy(obj))
                return true;
        }
        return false;
    }

    bool isFullyTriggeredBy(std::vector<Object*> activeObjs) const
    {
        for (auto const &t : triggers)
        {
            bool is_triggered = false;
            for (auto const& obj : activeObjs)
            {
                if (t.triggeredBy(obj))
                {
                    is_triggered = true;
                    break;
                }
            }

            if (!is_triggered)
                return false;
        }
        return true;
    }

    fillSlots := method(target, objs,
        if( objs == nil ,
            Exception raise("Referent fillSlots, objs list cannot be nil!")
        )
        triggers foreach(t,
            foundObj := false
            objs foreach(obj,
                if(t triggeredBy(obj),
                    target setSlot(t withSlot, obj)
                    foundObj = true
                )
            )
            if(foundObj not,
                Exception raise("Error, failed to find an object for interaction slot " .. t withSlot)
            )
        )
        return target
    )
};

}
