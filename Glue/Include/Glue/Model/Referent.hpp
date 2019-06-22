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
        for (Trigger const& t : triggers)
        {
            if (t.triggeredBy(obj))
                return true;
        }
        return false;
    }

    bool isFullyTriggeredBy(std::vector<Object*> const& activeObjs) const
    {
        for (Trigger const& t : triggers)
        {
            bool is_triggered = false;
            for (Object* obj : activeObjs)
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

    void fillSlots(Object* target, std::vector<Object*> const& activeObjs) const
    {
        for (Trigger const& t : triggers)
        {
            bool foundObj = false;
            for (Object* obj : activeObjs)
            {
                if (t.triggeredBy(obj))
                {
                    target->setSlot(obj);
                }
            }
            if (!foundObj)
                throw std::logic_error("No object found for one of the interaction slots");
        }
    }
};

}
