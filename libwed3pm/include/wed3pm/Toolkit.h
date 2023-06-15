#ifndef wed3pm_Toolkit_H
#define wed3pm_Toolkit_H

#include <string>
#include <chrono>

namespace wed3pm {

    class Toolkit {
    protected:
        using time_point = std::chrono::system_clock::time_point;

    public:
        virtual ~Toolkit() {}
        virtual auto getCurrentTime() const -> time_point = 0;
        virtual auto sleepUntil(const time_point& time) const -> void = 0;
        virtual auto broadcastMessage(const std::string& m) const -> void = 0;
    };
}

#endif
