#include "ComponentRegistry.h"

namespace EngineCore {

    ComponentRegistry& ComponentRegistry::Get() {
        static ComponentRegistry instance;
        return instance;
    }

    void ComponentRegistry::RegisterComponent(
        const std::string& name,
        ComponentFactory factory,
        const std::vector<std::string>& autoAdd
    ) {
        components[name] = { factory, autoAdd };
    }

    void ComponentRegistry::AddComponentToEntity(Entity& entity, const std::string& name) {
        if (entity.HasComponent(name)) return;

        auto it = components.find(name);
        if (it == components.end()) return;

        // Add dependencies first
        for (const auto& dep : it->second.autoAdd) {
            AddComponentToEntity(entity, dep);
        }

        entity.AddComponent(it->second.factory());
    }

}
