#include <Engine/Log.h>

namespace Engine
{
    Log::Log(NativeLogEvent::Bus* bus) : log_bus(bus)
    {
    }

    void Log::info(const std::string& message)
    {
        log_bus->dispatch(&NativeLogEvent::on_info, message);
    }
}