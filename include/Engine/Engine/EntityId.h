#pragma once

namespace Engine {
    using EntityId = unsigned long long;

    class WithEntityId {
        EntityId entity_id;
    public:
        WithEntityId(const EntityId& entity_id);
        EntityId get_entity_id() const;
    };
}
