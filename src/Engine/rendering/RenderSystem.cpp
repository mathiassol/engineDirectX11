#include "RenderSystem.h"
#include "../Engine.h"

namespace EngineCore {

    RenderSystem::RenderSystem(std::unique_ptr<IRenderer> renderer)
        : renderer(std::move(renderer)) {}

    void RenderSystem::Update(double /*dt*/) {
        renderer->BeginFrame();

        auto& engine = Engine::Get();

        for (auto& e : engine.GetAllEntities()) {
            if (e->HasComponent("Mesh") && e->HasComponent("Transform")) {
                renderer->DrawEntity(*e);
            }
        }

        renderer->EndFrame();
    }

    Entity* RenderSystem::GetActiveCamera() {
        auto& engine = Engine::Get();

        for (auto& e : engine.GetAllEntities()) {
            if (e->HasComponent("Camera")) {
                auto* cam = static_cast<Camera*>(e->GetComponent("Camera"));
                if (cam->primary)
                    return e.get();
            }
        }
        return nullptr;
    }

}
