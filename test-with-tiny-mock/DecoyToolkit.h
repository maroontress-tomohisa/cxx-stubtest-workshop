#ifndef DecoyToolkit_H
#define DecoyToolkit_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "wed3pm/Toolkit.h"
#include "tinymock/Scenario.h"

class DecoyToolkit final : public wed3pm::Toolkit {
private:
    tinymock::Scenario<Toolkit>& scenario;

public:
    explicit DecoyToolkit(tinymock::Scenario<Toolkit>& scenario):
            scenario(scenario) {
    }

    virtual auto getCurrentTime() const -> time_point override {
        auto call = scenario.nextCall();
        auto params = call.assertEquals(&Toolkit::getCurrentTime);
        params.assertEmpty();
        return call.getReturnValue<time_point>();
    }

    virtual auto sleepUntil(const time_point& time) const -> void override {
        auto call = scenario.nextCall();
        auto params = call.assertEquals(&Toolkit::sleepUntil);
        params.assertEquals(time)
            .assertEmpty();
    }

    virtual auto broadcastMessage(const std::string& m) const -> void override {
        auto call = scenario.nextCall();
        auto params = call.assertEquals(&Toolkit::broadcastMessage);
        params.assertEquals(m)
            .assertEmpty();
    }
};

#endif
