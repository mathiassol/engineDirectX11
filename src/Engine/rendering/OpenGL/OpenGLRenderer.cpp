#include "OpenGLRenderer.h"

namespace EngineCore {

    void OpenGLRenderer::Initialize(void* /*windowHandle*/) {
        // init glad, shaders, etc
    }

    void OpenGLRenderer::BeginFrame() {
        // glClear
    }

    void OpenGLRenderer::DrawEntity(const Entity& /*entity*/) {
        // bind mesh + draw
    }

    void OpenGLRenderer::EndFrame() {
        // swap buffers
    }

}
