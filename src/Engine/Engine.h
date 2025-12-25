#pragma once
#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "Entity.h"
#include "ComponentRegistry.h"
#include "SystemScheduler.h"
#include "rendering/RenderBackend.h"

namespace EngineCore {

    class Engine {
    public:
        static Engine& Get();

        Entity& CreateEntity(const std::string& name);
        Entity* GetRoot();

        const std::vector<std::unique_ptr<Entity>>& GetAllEntities();

        void InitializeRenderer(RenderBackend backend, void* windowHandle);

        void AddUpdateSystem(std::function<void(double)> func,
                             const UpdateSettings& settings = {});

        void Run();
        void Stop();

    private:
        Engine();
        void RegisterDefaultComponents();


        bool running = true;
        Entity::EntityID nextID = 1;

        std::vector<std::unique_ptr<Entity>> entities;
        Entity* root = nullptr;

        SystemScheduler scheduler;
    };

}
