#pragma once
#include "../Component.h"

namespace EngineCore {

    struct Scale : public Component {
        float x = 1, y = 1, z = 1;
        std::string GetTypeName() const override { return "Scale"; }
    };

}
