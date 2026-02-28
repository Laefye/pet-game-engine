#include <Engine/Component.h>

namespace Engine {
    Component::Component(const WithEntityId* entity_id) : entity_id(entity_id) {}

    EntityId Component::get_entity_id() const {
        return entity_id->get_entity_id();
    }
}
