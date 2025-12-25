#pragma once
#include <string>

namespace EngineCore {

    struct Component {
        virtual ~Component() = default;
        virtual std::string GetTypeName() const = 0;
    };

}
