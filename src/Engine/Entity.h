#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "Component.h"

namespace EngineCore {

    class Entity {
    public:
        using EntityID = uint64_t;

        Entity(EntityID id, const std::string& name);

        EntityID GetID() const;
        const std::string& GetName() const;

        // Hierarchy
        void SetParent(Entity* parent);
        Entity* GetParent() const;
        const std::vector<Entity*>& GetChildren() const;

        // Components
        void AddComponent(std::unique_ptr<Component> component);
        bool HasComponent(const std::string& type) const;
        Component* GetComponent(const std::string& type);

    private:
        EntityID id;
        std::string name;

        Entity* parent = nullptr;
        std::vector<Entity*> children;

        std::unordered_map<std::string, std::unique_ptr<Component>> components;
    };

}
