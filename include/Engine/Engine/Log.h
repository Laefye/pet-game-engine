#pragma once
#include <Engine/EventBus.h>
#include <string>

namespace Engine
{
    class NativeLogEvent
    {
    public:
        ~NativeLogEvent() = default;

        using Bus = Engine::EventBus<NativeLogEvent>;

        virtual void on_info(const std::string& message) = 0;
    };

    class Log
    {
        NativeLogEvent::Bus* log_bus;
    public:
        Log(NativeLogEvent::Bus* bus);

        void info(const std::string& message);
    };
}
