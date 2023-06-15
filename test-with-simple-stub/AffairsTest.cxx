#include <string>
#include <gtest/gtest.h>
#include "wed3pm/Affairs.h"
#include "DecoyToolkit.h"

TEST(AffairsTest, onWedSnackTime)
{
    // 2023年4月5日の15時に実行した場合は、放送してから、
    // 4月12日の15時までスリープしようとする
    auto logger = DecoyToolkit::Logger {};
    auto t = wed3pm::Affairs::newTimePoint(2023, 4, 5, 15);
    auto kit = DecoyToolkit {t, logger};
    wed3pm::Affairs::broadcastOnTime(kit);
    auto actual = logger.str();
    auto expected = std::string {
        "getCurrentTime() -> Wed Apr  5 15:00:00 2023\n"
        "broadcastMessage(今日は定時退社日です。計画的に業務を...\n)\n"
        "sleepUntil(Wed Apr 12 15:00:00 2023)\n"};
    ASSERT_EQ(actual, expected);
}

TEST(AffairsTest, onSatMidnight)
{
    // 2023年4月1日の0時に実行した場合は、放送はなくて、
    // 4月5日の15時までスリープしようとする
    auto logger = DecoyToolkit::Logger {};
    auto t = wed3pm::Affairs::newTimePoint(2023, 4, 1, 0);
    auto kit = DecoyToolkit {t, logger};
    wed3pm::Affairs::broadcastOnTime(kit);
    auto actual = logger.str();
    auto expected = std::string {
        "getCurrentTime() -> Sat Apr  1 00:00:00 2023\n"
        "sleepUntil(Wed Apr  5 15:00:00 2023)\n"};
    ASSERT_EQ(actual, expected);
}
