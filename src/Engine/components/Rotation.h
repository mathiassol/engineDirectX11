#pragma once
#include "../Component.h"

namespace EngineCore {

    struct Rotation : public Component {
        float pitch = 0, yaw = 0, roll = 0;
        std::string GetTypeName() const override { return "Rotation"; }
    };

}
