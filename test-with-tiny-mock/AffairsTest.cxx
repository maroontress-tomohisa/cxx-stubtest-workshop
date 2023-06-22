#include <string>
#include <gtest/gtest.h>
#include "wed3pm/Affairs.h"
#include "tinymock/ScenarioBuilder.h"
#include "DecoyBuilderToolkit.h"
#include "DecoyToolkit.h"

TEST(AffairsTest, onWedSnackTime)
{
    using namespace std::literals;
    auto t = wed3pm::Affairs::newTimePoint(2023, 4, 5, 15);
    auto e = wed3pm::Affairs::newTimePoint(2023, 4, 12, 15);
    auto m = "今日は定時退社日です。計画的に業務を...\n"s;

    auto scenarioBuilder = tinymock::ScenarioBuilder<wed3pm::Toolkit> {};
    auto kit = DecoyBuilderToolkit {scenarioBuilder};
    (void) kit.getCurrentTime();
    scenarioBuilder.lastCallReturns(t);
    kit.broadcastMessage(m);
    kit.sleepUntil(e);

    auto scenario = scenarioBuilder.build();
    auto mock = DecoyToolkit {scenario};
    wed3pm::Affairs::broadcastOnTime(mock);
    scenario.assertEmpty();
}

TEST(AffairsTest, onSatMidnight)
{
    using namespace std::literals::string_literals;
    auto t = wed3pm::Affairs::newTimePoint(2023, 4, 1, 0);
    auto e = wed3pm::Affairs::newTimePoint(2023, 4, 5, 15);

    auto scenarioBuilder = tinymock::ScenarioBuilder<wed3pm::Toolkit> {};
    auto kit = DecoyBuilderToolkit {scenarioBuilder};
    (void) kit.getCurrentTime();
    scenarioBuilder.lastCallReturns(t);
    kit.sleepUntil(e);

    auto scenario = scenarioBuilder.build();
    auto mock = DecoyToolkit {scenario};
    wed3pm::Affairs::broadcastOnTime(mock);
    scenario.assertEmpty();
}
