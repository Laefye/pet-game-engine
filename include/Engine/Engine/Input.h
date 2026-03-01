#pragma once
#include <Engine/EventBus.h>

namespace Engine {
    enum Key {
        Space, Console, Escape
    };

    class InputEvent {
    public:
        using Bus = EventBus<InputEvent>;

        virtual ~InputEvent() = default;

        virtual void on_key_down(Key key) = 0;
    };
}
