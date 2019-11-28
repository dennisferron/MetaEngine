#pragma once

#include "Glue/Constants.hpp"

#include "irrlicht.h"

#include <functional>
#include <set>
#include <vector>

namespace Glue {

enum class EventWhen
{
    before,
    on,
    after
};

enum class EventWhat
{
    frame,
    physics,
    graphics
};

using RelTime = Scalar;
using AbsTime = Scalar;

struct TimeInfo
{
    RelTime delta;
    AbsTime current;
    AbsTime last;
};

struct EngineEvent
{
    EventWhen when;
    EventWhat what;
    std::function<void(TimeInfo)> action;
};

struct TimeoutEvent
{
    AbsTime fromTime;
    AbsTime atTime;
    std::function<RelTime(RelTime)> action;

    bool operator <(TimeoutEvent const& that) const
    {
        return this->atTime < that.atTime;
    }

    bool operator <=(AbsTime const& nowTime) const
    {
        return this->atTime <= nowTime;
    }
};

class TimeComponent
{
private:

    std::multiset<TimeoutEvent> timeout_events;
    std::vector<EngineEvent> engine_events;

	irr::ITimer* deviceTimer = nullptr;
	AbsTime currentTime = 0;
	AbsTime lastTime = 0;

    volatile bool shouldRun = true;

	void _processTimeoutEvents();
    void doEvents(EventWhen when, EventWhat what) const;

public:

    TimeComponent(irr::ITimer* value);
	void setTimeout(RelTime delay, std::function<RelTime(RelTime)> action);
    RelTime elapsed() const;
    void runLoop();
    void add_handler(EventWhen when, EventWhat what, std::function<void(TimeInfo)> action);
};

}
