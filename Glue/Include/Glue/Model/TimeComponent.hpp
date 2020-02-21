#pragma once

#include "Glue/Constants.hpp"
#include "Glue/Model/ModelInterfaces.hpp"

#include "irrlicht.h"

#include <functional>
#include <set>
#include <vector>

namespace Glue
{

class TimeComponent : public ITimeComponent
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
	void setTimeout(RelTime delay, std::function<RelTime(RelTime)> action) final;
    RelTime elapsed() const final;
    void runLoop() final;
    void add_handler(EventWhen when, EventWhat what, std::function<void(TimeInfo)> action) final;
};

}
