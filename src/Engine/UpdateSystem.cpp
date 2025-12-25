#include "UpdateSystem.h"

namespace EngineCore {

    UpdateSystem::UpdateSystem(std::function<void(double)> func,
                               const UpdateSettings& settings)
        : function(func), settings(settings) {}

    void UpdateSystem::Tick(double deltaTime) {
        updateCounter++;
        timeAccumulator += deltaTime;

        // Check update-based condition
        if (settings.runEveryUpdates > 1) {
            if (updateCounter % settings.runEveryUpdates != 0)
                return;
        }

        // Check time-based condition
        if (settings.runEverySeconds > 0.0) {
            if (timeAccumulator < settings.runEverySeconds)
                return;

            timeAccumulator = 0.0;
        }

        function(deltaTime);
    }

}
