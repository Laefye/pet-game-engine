#pragma once
#include <vector>
#include <Engine/EntityId.h>
#include <Engine/Component.h>

namespace Engine {
    class Entity : public WithEntityId {
        std::vector<Component*> components;
    public:
        Entity(const EntityId& entity_id);
        ~Entity();

        template<typename T, typename... Args>
        T* new_component(Args&&... args) {
            T* component = new T(static_cast<const WithEntityId*>(this), std::forward<Args>(args)...);
            components.push_back(component);
            return component;
        }
    };
}