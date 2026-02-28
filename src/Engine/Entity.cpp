#include <Engine/Entity.h>

namespace Engine {
    Entity::Entity(const EntityId& entity_id) : WithEntityId(entity_id) {}

    Entity::~Entity() {
        for (Component* component : components) {
            delete component;
        }
    }
}
