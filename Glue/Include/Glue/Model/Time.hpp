#pragma once

#include "Constants.hpp"

#include "irrlicht.h"

#include <functional>
#include <set>

namespace Glue {

using ITimer = irr::ITimer;

enum class EventWhen
{
    Before,
    On,
    After
};

enum class EventWhat
{
    Frame,
    Physics,
    Graphics
};

using RelTime = Scalar;
using AbsTime = Scalar;

struct TimeInfo
{
    RelTime delta;
    AbsTime last;
    AbsTime current;
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

class Time
{
private:

    std::multiset<TimeoutEvent> timeout_events;
    std::vector<EngineEvent> engine_events;

	ITimer* deviceTimer = nullptr;
	AbsTime currentTime = 0;
	AbsTime lastTime = 0;

    volatile bool shouldRun = true;

	void _processTimeoutEvents();

public:

    Time& setDeviceTimer(ITimer* value);
	void setTimeout(RelTime delay, std::function<RelTime(RelTime)> action);
    RelTime elapsed() const;
    void runLoop();
    void doEvents(EventWhen when, EventWhat what);
};

}
