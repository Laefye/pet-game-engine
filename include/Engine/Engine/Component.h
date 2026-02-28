#pragma once
#include <Engine/EntityId.h>
#include <Engine/EventBus.h>

namespace Engine {
    class Component {
        const WithEntityId* entity_id;
    protected:
        EntityId get_entity_id() const;
    public:
        Component(const WithEntityId* entity_id);
        virtual ~Component() = default;

        template <typename E, typename S>
        void connect(S* self, EventBus<E>* bus) {
            bus->subscribe(get_entity_id(), static_cast<E*>(self));
        }

        template <typename E, typename S>
        void disconnect(S* self, EventBus<E>* bus) {
            bus->unsubscribe(get_entity_id(), static_cast<E*>(self));
        }
    };
}
