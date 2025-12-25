#pragma once
#include <vector>

namespace EngineCore {

    class Entity;

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        virtual void Initialize(void* windowHandle) = 0;
        virtual void BeginFrame() = 0;
        virtual void DrawEntity(const Entity& entity) = 0;
        virtual void EndFrame() = 0;
    };

}
