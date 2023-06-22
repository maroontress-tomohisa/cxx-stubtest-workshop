#include <string>
#include <gtest/gtest.h>
#include "wed3pm/Affairs.h"
#include "wed3pm/GoodAffair.h"
#include "DecoyToolkit.h"

TEST(GoodAffairTest, onWedSnackTime)
{
    // 2023年4月5日の15時に実行した場合は、放送してから、
    // 同日の15:00:01時までスリープしようとする

    // AffairsTestを参考にして書いてみる
}

TEST(GoodAffairTest, onSatMidnight)
{
    // 2023年4月1日の0時に実行した場合は、放送はなくて、
    // 同日の00:00:01までスリープしようとする
    auto logger = DecoyToolkit::Logger {};
    auto t = wed3pm::Affairs::newTimePoint(2023, 4, 1, 0);
    auto kit = DecoyToolkit {t, logger};
    auto affair = wed3pm::GoodAffair {};
    affair.broadcastOnTime(kit);
    auto actual = logger.str();
    auto expected = std::string {
        "getCurrentTime() -> Sat Apr  1 00:00:00 2023\n"
        "sleepUntil(Sat Apr  1 00:00:01 2023)\n"};
    ASSERT_EQ(actual, expected);
}
