#pragma once
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>

#include "Component.h"
#include "Entity.h"

namespace EngineCore {

    class ComponentRegistry {
    public:
        using ComponentFactory = std::function<std::unique_ptr<Component>()>;

        static ComponentRegistry& Get();

        void RegisterComponent(
            const std::string& name,
            ComponentFactory factory,
            const std::vector<std::string>& autoAdd = {}
        );


        void AddComponentToEntity(Entity& entity, const std::string& name);

    private:
        struct ComponentInfo {
            ComponentFactory factory;
            std::vector<std::string> autoAdd;
        };

        std::unordered_map<std::string, ComponentInfo> components;
    };

}
