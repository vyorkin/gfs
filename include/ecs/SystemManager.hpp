#pragma once

#include "Prerequisites.hpp"
#include "UidRegistry.hpp"
#include "ecs/System.hpp"

namespace gfs {
    namespace ecs {
        class SystemManager final {
            public:
                SystemManager(World* world);
                ~SystemManager();

                SystemSet getSystems() const;
                void process();

                template<class S> S* add(S* system) {
                    const auto uid = uidRegistry->get<S>();

                    system->world = world;
                    system->uidRegistry = uidRegistry;
                    system->bits.system = uid.getBit();

                    system->initialize();

                    systems.insert(std::make_pair(uid, system));

                    return system;
                }

                template<class S> S* get() const {
                    const auto uid = uidRegistry->get<S>();
                    auto it = systems.find(uid);

                    return it == systems.cend() ?
                        nullptr : dynamic_cast<S*>(it->second);
                }

            private:
                World* world;
                UidRegistry* uidRegistry;
                SystemMap systems;
        };
    }
}
