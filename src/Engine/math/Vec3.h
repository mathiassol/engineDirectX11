#pragma once
#include <cmath>

namespace EngineCore {

    struct Vec3 {
        float x = 0, y = 0, z = 0;

        Vec3() = default;
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    };

}
