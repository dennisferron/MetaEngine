#pragma once

#include <functional>

namespace Glue
{
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

    using RelTime = float;
    using AbsTime = float;

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

    class ITimeComponent
    {
    public:
        virtual ~ITimeComponent()
        {}

        virtual void setTimeout(RelTime delay, std::function<RelTime(RelTime)> action) = 0;

        virtual RelTime elapsed() const = 0;

        virtual void runLoop() = 0;

        virtual void add_handler(EventWhen when, EventWhat what, std::function<void(TimeInfo)> action) = 0;
    };
}