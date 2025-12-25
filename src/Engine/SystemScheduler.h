#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "UpdateSystem.h"

namespace EngineCore {

    class SystemScheduler {
    public:
        void AddSystem(std::function<void(double)> func,
                       const UpdateSettings& settings = {});

        void Update(double deltaTime);

    private:
        std::vector<std::unique_ptr<UpdateSystem>> systems;
    };

}
