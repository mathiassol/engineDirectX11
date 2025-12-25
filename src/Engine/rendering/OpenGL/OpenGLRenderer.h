#pragma once
#include "../IRenderer.h"

namespace EngineCore {

    class OpenGLRenderer : public IRenderer {
    public:
        void Initialize(void* windowHandle) override;
        void BeginFrame() override;
        void DrawEntity(const Entity& entity) override;
        void EndFrame() override;
    };

}
