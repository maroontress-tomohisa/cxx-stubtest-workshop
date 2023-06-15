#ifndef wed3pm_Affairs_H
#define wed3pm_Affairs_H

#include "wed3pm/Toolkit.h"

namespace wed3pm {

    class Affairs final {
    public:
        static auto newTimePoint(int year, int month, int day, int hour)
            -> std::chrono::system_clock::time_point;
        static auto broadcastOnTime(const Toolkit& kit) -> void;
    };
}

#endif
