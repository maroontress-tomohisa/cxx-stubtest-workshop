#ifndef DecoyBuilderToolkit_H
#define DecoyBuilderToolkit_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "wed3pm/Toolkit.h"
#include "tinymock/ScenarioBuilder.h"

class DecoyBuilderToolkit final : public wed3pm::Toolkit {
private:
    tinymock::ScenarioBuilder<Toolkit>& builder;

public:
    explicit DecoyBuilderToolkit(
            tinymock::ScenarioBuilder<Toolkit>& builder):
            builder(builder) {
    }

    virtual auto getCurrentTime() const -> time_point override {
        auto newCall = builder.newCall();
        builder.add(newCall(&wed3pm::Toolkit::getCurrentTime));
        return time_point {};
    }

    virtual auto sleepUntil(const time_point& time) const -> void override {
        auto newCall = builder.newCall();
        builder.add(newCall(&wed3pm::Toolkit::sleepUntil)
            .with(time));
    }

    virtual auto broadcastMessage(const std::string& m) const -> void override {
        auto newCall = builder.newCall();
        builder.add(newCall(&wed3pm::Toolkit::broadcastMessage)
            .with(m));
    }
};

#endif
