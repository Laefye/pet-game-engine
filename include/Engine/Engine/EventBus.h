#pragma once
#include <vector>
#include <algorithm>
#include <Engine/EntityId.h>
#include <map>
#include <utility>
#include <ranges>


namespace Engine
{
    template<class E>
    class EventBus
    {
        std::vector<E*> listeners;
        std::map<EntityId, E*> listeners_by_entity_id;
    public:
        EventBus() = default;
        EventBus(const EventBus&) = delete;

        void subscribe(E* listener)
        {
            listeners.push_back(listener);
        }

        void subscribe(EntityId entity_id, E* listener)
        {
            listeners_by_entity_id[entity_id] = listener;
        }

        void unsubscribe(E* listener)
        {
            listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
        }

        void unsubscribe(EntityId entity_id, E* listener)
        {
            listeners_by_entity_id.erase(entity_id);
        }

        template<typename... Args>
        void dispatch(void (E::*callback)(Args...), Args&&... args)
        {
            for (auto* listener : listeners)
            {
                (listener->*callback)(std::forward<Args>(args)...);
            }
        }

        template<typename... Args>
        void dispatch(void (E::*callback)(Args...) const, Args&&... args) const
        {
            for (auto* listener : listeners)
            {
                (listener->*callback)(std::forward<Args>(args)...);
            }
        }

        template<typename... Args>
        void broadcast(void (E::*callback)(Args...), Args&&... args)
        {
            dispatch(callback, std::forward<Args>(args)...);

            std::vector<EntityId> keys;
            keys.reserve(listeners_by_entity_id.size());
            for (const auto& [key, _] : listeners_by_entity_id) {
                keys.push_back(key);
            }
            std::ranges::sort(keys);

            for (const auto& key : keys) {
                (listeners_by_entity_id.at(key)->*callback)(std::forward<Args>(args)...);
            }
        }

        template<typename... Args>
        void broadcast(void (E::*callback)(Args...) const, Args&&... args) const
        {
            dispatch(callback, std::forward<Args>(args)...);

            std::vector<EntityId> keys;
            keys.reserve(listeners_by_entity_id.size());
            for (const auto& [key, _] : listeners_by_entity_id) {
                keys.push_back(key);
            }
            std::ranges::sort(keys);

            for (const auto& key : keys) {
                (listeners_by_entity_id.at(key)->*callback)(std::forward<Args>(args)...);
            }
        }

        template<typename... SourceArgs, typename... Args>
        void to_entity(EntityId entity_id, void (E::*callback)(Args...), SourceArgs&&... args)
        {
            if (listeners_by_entity_id.find(entity_id) != listeners_by_entity_id.end()) {
                (listeners_by_entity_id.at(entity_id)->*callback)(std::forward<Args>(static_cast<Args>(args))...);
            }
        }

        template<typename... SourceArgs, typename... Args>
        void to_entity(EntityId entity_id, void (E::*callback)(Args...) const, SourceArgs&&... args) const
        {
            if (listeners_by_entity_id.find(entity_id) != listeners_by_entity_id.end()) {
                (listeners_by_entity_id.at(entity_id)->*callback)(std::forward<Args>(static_cast<Args>(args))...);
            }
        }
    };
}
