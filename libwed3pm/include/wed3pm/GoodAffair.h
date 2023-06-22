#ifndef wed3pm_GoodAffair_H
#define wed3pm_GoodAffair_H

#include <ctime>
#include <optional>
#include "Toolkit.h"

namespace wed3pm {

    class GoodAffair {
    private:
        std::optional<std::time_t> lastTime;

    public:
        auto broadcastOnTime(const Toolkit& kit) -> void {
            auto now = kit.getCurrentTime();
            auto t = std::chrono::system_clock::to_time_t(now);
            auto local = std::tm {*std::localtime(&t)};
            local.tm_sec = 0;
            auto u = std::mktime(&local);
            if (local.tm_wday == 3
                    && local.tm_hour == 15
                    && local.tm_min == 0
                    && (!lastTime.has_value() || lastTime.value() < u)) {
                auto m = "今日は定時退社日です。計画的に業務を...\n";
                kit.broadcastMessage(m);
                lastTime = std::make_optional(u);
            }
            auto v = now + std::chrono::seconds(1);
            kit.sleepUntil(v);
        }
    };

}

#endif
