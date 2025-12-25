#include "Entity.h"

namespace EngineCore {

    Entity::Entity(EntityID id, const std::string& name)
        : id(id), name(name) {}

    Entity::EntityID Entity::GetID() const { return id; }
    const std::string& Entity::GetName() const { return name; }

    void Entity::SetParent(Entity* newParent) {
        parent = newParent;
        if (parent) {
            parent->children.push_back(this);
        }
    }

    Entity* Entity::GetParent() const { return parent; }
    const std::vector<Entity*>& Entity::GetChildren() const { return children; }

    void Entity::AddComponent(std::unique_ptr<Component> component) {
        components[component->GetTypeName()] = std::move(component);
    }

    bool Entity::HasComponent(const std::string& type) const {
        return components.find(type) != components.end();
    }

    Component* Entity::GetComponent(const std::string& type) {
        auto it = components.find(type);
        return it != components.end() ? it->second.get() : nullptr;
    }

}
