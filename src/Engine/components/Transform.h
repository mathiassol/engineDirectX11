#pragma once
#include "../Component.h"
#include <string>

namespace EngineCore {

    struct Transform : public Component {
        float x = 0, y = 0, z = 0;
        std::string GetTypeName() const override { return "Transform"; }
    };

}
