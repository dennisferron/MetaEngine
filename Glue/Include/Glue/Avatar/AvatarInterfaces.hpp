#pragma once

namespace Glue
{
    class INode;
    struct TimeInfo;
}

namespace Glue::Avatar
{

    class IAvatarAttribute
    {
    public:
        virtual ~IAvatarAttribute() {}

        virtual bool canJump() = 0;
        virtual void dive() = 0;
        virtual void jump() = 0;
        virtual void right() = 0;
        virtual void left() = 0;
    };

    class IAvatarComponent : public IGraphObserver
    {
    public:
        virtual ~IAvatarComponent() {}

        virtual void attachControl(INode* node) = 0;
        virtual void beforePhysics(TimeInfo const&) = 0;
    };

}