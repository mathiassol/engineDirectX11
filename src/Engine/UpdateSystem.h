#pragma once
#include <functional>

namespace EngineCore {

    struct UpdateSettings {
        int runEveryUpdates = 1;     // 1 = every update
        double runEverySeconds = 0;  // 0 = disabled
    };

    class UpdateSystem {
    public:
        UpdateSystem(std::function<void(double)> func,
                     const UpdateSettings& settings);

        void Tick(double deltaTime);

    private:
        std::function<void(double)> function;
        UpdateSettings settings;

        int updateCounter = 0;
        double timeAccumulator = 0.0;
    };

}
