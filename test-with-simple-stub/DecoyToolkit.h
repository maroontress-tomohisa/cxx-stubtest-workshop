#ifndef DecoyToolkit_H
#define DecoyToolkit_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "wed3pm/Toolkit.h"

class DecoyToolkit final : public wed3pm::Toolkit {
public:
    using Logger = std::ostringstream;

private:
    time_point time;
    Logger& logger;

    auto localTime(time_point p) const {
        auto t = std::chrono::system_clock::to_time_t(p);
        auto local = std::localtime(&t);
        return std::put_time(local, "%c");
    }

public:
    explicit DecoyToolkit(const time_point& time, Logger& logger)
            : time(time), logger(logger) {
    }

    virtual auto getCurrentTime() const -> time_point override {
        logger << "getCurrentTime() -> " << localTime(time) << "\n";
        return time;
    }

    virtual auto sleepUntil(const time_point& time) const
            -> void override {
        logger << "sleepUntil(" << localTime(time) << ")\n";
    }

    virtual auto broadcastMessage(const std::string& m) const
            -> void override {
        logger << "broadcastMessage(" << m << ")\n";
    }
};

#endif
