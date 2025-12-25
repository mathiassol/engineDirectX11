#include "SystemScheduler.h"

namespace EngineCore {

    void SystemScheduler::AddSystem(std::function<void(double)> func,
                                    const UpdateSettings& settings) {
        systems.push_back(std::make_unique<UpdateSystem>(func, settings));
    }

    void SystemScheduler::Update(double deltaTime) {
        for (auto& system : systems) {
            system->Tick(deltaTime);
        }
    }

}
