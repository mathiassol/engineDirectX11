#pragma once
#include "../Component.h"
#include <string>

namespace EngineCore {

    struct Mesh : public Component {
        std::string meshType;
        std::string GetTypeName() const override { return "Mesh"; }
    };

}
