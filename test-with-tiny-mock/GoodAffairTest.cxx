#include <string>
#include <gtest/gtest.h>
#include "wed3pm/Affairs.h"
#include "wed3pm/GoodAffair.h"
#include "tinymock/ScenarioBuilder.h"
#include "DecoyBuilderToolkit.h"
#include "DecoyToolkit.h"

using namespace std::literals;
using ScenarioBuilder = tinymock::ScenarioBuilder<wed3pm::Toolkit>;
using Scenario = tinymock::Scenario<wed3pm::Toolkit>;

static const std::string m = "今日は定時退社日です。計画的に業務を...\n"s;

static auto scenarioOnWed3pm(wed3pm::Toolkit& kit,
    ScenarioBuilder& builder) -> void
{
    auto t = wed3pm::Affairs::newTimePoint(2023, 4, 5, 15, 0, 0);
    auto e = wed3pm::Affairs::newTimePoint(2023, 4, 5, 15, 0, 1);

    (void) kit.getCurrentTime();
    builder.lastCallReturns(t);
    kit.broadcastMessage(m);
    kit.sleepUntil(e);
}

static auto scenarioOnWed3pmAfterFirstTime(wed3pm::Toolkit& kit,
    ScenarioBuilder& builder) -> void
{
    auto t = wed3pm::Affairs::newTimePoint(2023, 4, 5, 15, 0, 1);
    auto e = wed3pm::Affairs::newTimePoint(2023, 4, 5, 15, 0, 2);

    (void) kit.getCurrentTime();
    builder.lastCallReturns(t);
    kit.sleepUntil(e);
}

static auto testBroadcastOnTime(Scenario&& scenario, int count) -> void
{
    auto kit = DecoyToolkit {scenario};
    auto affair = wed3pm::GoodAffair {};
    for (auto k = 0; k < count; ++k) {
        affair.broadcastOnTime(kit);
    }
    scenario.assertEmpty();
}

TEST(GoodAffairTest, onWed3pmFirstTime)
{
    auto builder = ScenarioBuilder {};
    auto kit = DecoyBuilderToolkit {builder};
    scenarioOnWed3pm(kit, builder);
    testBroadcastOnTime(builder.build(), 1);
}

TEST(GoodAffairTest, onWed3pmFirstAndSecondTime)
{
    auto builder = ScenarioBuilder {};
    auto kit = DecoyBuilderToolkit {builder};
    scenarioOnWed3pm(kit, builder);
    scenarioOnWed3pmAfterFirstTime(kit, builder);
    testBroadcastOnTime(builder.build(), 2);
}
