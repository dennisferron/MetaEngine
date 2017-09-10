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

Time& Time::setDeviceTimer(ITimer* value)
{
    deviceTimer = value;
}

void Time::setTimeout(RelTime delay, std::function<RelTime(RelTime)> action)
{
    AbsTime fromTime = currentTime;
    AbsTime atTime = fromTime + delay;
    TimeoutEvent evt({fromTime, atTime, action});
    timeout_events.insert(evt);
}

RelTime Time::elapsed() const
{
    retur currentTime - lastTime;
}

void Time::runLoop()
{
    while(shouldRun)
    {
        lastTime = currentTime;
        currentTime = deviceTimer->getTime();

        doEvents(EventWhen::before, EventWhat::frame);

        _processTimeoutEvents();

        doEvents(EventWhen::before, EventWhat::physics);
        doEvents(EventWhen::on, EventWhat::physics);
        doEvents(EventWhen::after, EventWhat::physics);

        doEvents(EventWhen::on, EventWhat::frame);

        doEvents(EventWhen::before, EventWhat::graphics);
        doEvents(EventWhen::on, EventWhat::graphics);
        doEvents(EventWhen::after, EventWhat::graphics);

        doEvents(EventWhen::after, EventWhat::frame);
    }
}

void Time::doEvents(EventWhen when, EventWhat what) const
{
    for (auto const& ee : engine_events)
        if (ee.when == when && ee.what == what)
            ee.action(TimeInfo {currentTime - lastTime, currentTime, lastTime});
}

void Time::add_handler(EventWhen when, EventWhat what, std::function<void(TimeInfo)> action)
{
    engine_events.push_back(EngineEvent {when, what, action});
}

}
