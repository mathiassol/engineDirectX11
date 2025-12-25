#pragma once
#include <memory>

#include "../SystemScheduler.h"
#include "../Entity.h"
#include "IRenderer.h"
#include "../components/Camera.h"

namespace EngineCore {

    class RenderSystem {
    public:
        RenderSystem(std::unique_ptr<IRenderer> renderer);

        void Update(double dt);

    private:
        std::unique_ptr<IRenderer> renderer;

        Entity* GetActiveCamera();
    };

}
