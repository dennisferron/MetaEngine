#pragma once

#include "Model/Time.hpp"

namespace Glue {

Time::Time() :
	deviceTimer(nullptr),
	currentTime(0),
	lastTime(0),
    shouldRun(true)
{
}

void Time::_processTimeoutEvents()
{
    auto erase_to = timeout_events.begin();
    std::vector<TimeoutEvent> new_events;

    try
    {
        for (auto iter = timeout_events.begin(); iter < timeout_events.end(); ++iter)
        {
            TimeoutEvent evt(*iter);

            if (evt.atTime <= currentTime)
            {
                erase_to = iter + 1;
                RelTime result = evt.action(currentTime - fromTime);
                if (result > 0)
                    setTimeout(result, evt.action);
            }
            else
            {
                // Since the multiset is in order, once we reach an atTime > currentTime
                // we can stop because the rest of the list will also be > currentTime.
                break;
            }
        }

        timeout_events.erase(timeout_events.begin(), erase_to);
        timeout_events.insert(new_events.begin(), new_events.end());
    }
    catch (...)
    {
        // If we encounter an exception during event processing, we still want to
        // remove the processed events.  This does two things.  First, it avoids
        // inadvertently double-processing events.  Second, it gets the event which
        // threw the exception off of the list.  We go ahead and add the new events
        // too so that e.g. a GUI doesn't lock up because its events went unrenewed.
        // The result of the event which threw the exception will not be in the new
        // events list anyway (because there was no return value).
        timeout_events.erase(timeout_events.begin(), erase_to);
        timeout_events.insert(new_events.begin(), new_events.end());
        throw;  // Catch and release.
    }
}

Time& Time::setDeviceTimer(ITimer* value);
void Time::setTimeout(RelTime delay, std::function<RelTime(RelTime)> action);
RelTime Time::elapsed() const;
void Time::runLoop();
void Time::doEvents(EventWhen when, EventWhat what);

}


method(

Time := Object clone lexicalDo(

	events ::= nil
	deviceTimer ::= nil
	currentTime := 0
	lastTime := 0

    shouldRun ::= nil

    beforeFrame ::= nil
    beforePhysics ::= nil
    onPhysics ::= nil
    afterPhysics ::= nil
    beforeGraphics ::= nil
    onGraphics ::= nil
    afterGraphics ::= nil
    afterFrame ::= nil

	init := method(
        setEvents(List clone)

        setBeforeFrame(List clone)
        setBeforePhysics(List clone)
        setOnPhysics(List clone)
        setAfterPhysics(List clone)
        setBeforeGraphics(List clone)
        setOnGraphics(List clone)
        setAfterGraphics(List clone)
        setAfterFrame(List clone)
    )

    setDeviceTimer := method(value,
        deviceTimer = value
        currentTime = deviceTimer call
        lastTime = currentTime
        self
    )

	Event := Object clone do(
		atTime ::= nil
		action ::= nil
	)

	_processEvents := method(
		tempList := events clone
		tempList foreach(e,
			if(e atTime <= currentTime,
				nextTime := e action call
				if(nextTime > 0, setTimeout(nextTime, e action))
				events remove(e)
			)
		)

		/*
		while(events first != nil and events first atTime <= currentTime,
			e := events removeFirst
			nextTime := e action call
			if(nextTime > 0, setTimeout(nextTime, e action))
		)
		*/
	)

	_getEventPos := method(atTime,
		// Linear search; change to better algorithm if adding events gets slow.
		events foreach(i, v,
			if(v atTime >= atTime,
				return i
			)
		)
		return 0
	)

	setTimeout := method(delay, action,
		atTime := currentTime + delay
        events insertAt(
            Event clone setAtTime(atTime) setAction(action),
            _getEventPos(atTime)
        )
	)

	elapsed := method(currentTime - lastTime)

    runLoop := method(

        if( deviceTimer == nil,
            Exception raise("No deviceTimer set up in Time component.")
        )

        //Profiler profile(
            while(shouldRun call,

                lastTime = currentTime
                currentTime = deviceTimer call

                doEvent(beforeFrame)

                _processEvents

                doEvent(beforePhysics)
                doEvent(onPhysics)
                doEvent(afterPhysics)

                doEvent(beforeGraphics)
                doEvent(onGraphics)
                doEvent(afterGraphics)

                doEvent(afterFrame)
            )
        //)  // end Profiler profile
    )

    doEvent := method(handlerList,
        handlerList foreach(handler,
            handler call(currentTime - lastTime, currentTime, lastTime)
        )
    )
)

)
