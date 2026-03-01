#pragma once
#include <Engine/Log.h>

namespace Engine::Native {
    class ConsoleOpener {
    public:
        virtual ~ConsoleOpener() = default;

        virtual void open_console() = 0;
        virtual void close_console() = 0;
        virtual NativeLogEvent::Bus *get_log_bus() = 0;
    };
}
