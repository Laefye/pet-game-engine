#include <Engine/EntityId.h>

namespace Engine {
    WithEntityId::WithEntityId(const EntityId& entity_id) : entity_id(entity_id) {}

    EntityId WithEntityId::get_entity_id() const {
        return entity_id;
    }
}