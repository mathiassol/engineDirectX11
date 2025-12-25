#include "Engine.h"
#include <chrono>
#include <thread>

#include "rendering/RenderSystem.h"
#include "rendering/RenderBackend.h"
#include "rendering/OpenGL/OpenGLRenderer.h"
#include "rendering/DirectX11/DX11Renderer.h"

#include "components/Transform.h"
#include "components/Rotation.h"
#include "components/Scale.h"
#include "components/Mesh.h"
#include  "components/camera.h"


namespace EngineCore {

    // ---------- Singleton ----------
    Engine& Engine::Get() {
        static Engine instance;
        return instance;
    }

    // ---------- Constructor ----------
    Engine::Engine() {
        root = &CreateEntity("Root");
        RegisterDefaultComponents();
    }

    // ---------- Entity API ----------
    Entity& Engine::CreateEntity(const std::string& name) {
        entities.push_back(std::make_unique<Entity>(nextID++, name));
        return *entities.back();
    }

    Entity* Engine::GetRoot() {
        return root;
    }

    const std::vector<std::unique_ptr<Entity>>& Engine::GetAllEntities() {
        return entities;
    }

    // ---------- Systems ----------
    void Engine::AddUpdateSystem(std::function<void(double)> func,
                                 const UpdateSettings& settings) {
        scheduler.AddSystem(func, settings);
    }

    // ---------- Main Loop ----------
    void Engine::Run() {
        using clock = std::chrono::high_resolution_clock;
        auto last = clock::now();

        while (running) {
            auto now = clock::now();
            std::chrono::duration<double> delta = now - last;
            last = now;

            scheduler.Update(delta.count());

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    std::unique_ptr<RenderSystem> renderSystem;

    void Engine::InitializeRenderer(RenderBackend backend, void* windowHandle) {
        std::unique_ptr<IRenderer> renderer;

        if (backend == RenderBackend::OpenGL)
            renderer = std::make_unique<OpenGLRenderer>();
        else
            renderer = std::make_unique<DX11Renderer>();

        renderer->Initialize(windowHandle);
        renderSystem = std::make_unique<RenderSystem>(std::move(renderer));

        AddUpdateSystem([this](double dt) {
            renderSystem->Update(dt);
        });
    }

    void Engine::Stop() {
        running = false;
    }

    // ---------- Component Registration ----------
    void Engine::RegisterDefaultComponents() {
        auto& reg = ComponentRegistry::Get();

        reg.RegisterComponent("Transform", []() {
            return std::make_unique<Transform>();
        });

        reg.RegisterComponent("Rotation", []() {
            return std::make_unique<Rotation>();
        });

        reg.RegisterComponent("Scale", []() {
            return std::make_unique<Scale>();
        });

        reg.RegisterComponent("Camera", []() {
            return std::make_unique<Camera>();
        });

        reg.RegisterComponent(
            "Mesh",
            []() {
                auto m = std::make_unique<Mesh>();
                m->meshType = "Cube";
                return m;
            },
            { "Transform", "Rotation", "Scale" }
        );
    }


}
