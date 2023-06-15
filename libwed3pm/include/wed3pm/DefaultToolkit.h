#ifndef wed3pm_DefaultToolkit_H
#define wed3pm_DefaultToolkit_H

#include <iostream>
#include <thread>
#include "wed3pm/Toolkit.h"

namespace wed3pm {

    class DefaultToolkit final : public Toolkit {
    public:
        virtual auto getCurrentTime() const -> time_point override {
            return std::chrono::system_clock::now();
        }

        virtual auto sleepUntil(const time_point& time) const
                -> void override {
            std::this_thread::sleep_until(time);
        }

        virtual auto broadcastMessage(const std::string& m) const
                -> void override {
            std::cout << m;
        }
    };
}

#endif
