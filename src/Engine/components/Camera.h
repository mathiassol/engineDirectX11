#pragma once
#include "../Component.h"

namespace EngineCore {

    struct Camera : public Component {
        float fov = 60.0f * 3.14159f / 180.0f;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;
        bool primary = true;
    };



}
