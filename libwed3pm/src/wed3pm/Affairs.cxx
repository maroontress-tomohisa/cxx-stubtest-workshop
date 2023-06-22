#include "wed3pm/Affairs.h"

auto
wed3pm::Affairs::newTimePoint(int year, int month, int day, int hour,
    int min, int sec) -> std::chrono::system_clock::time_point
{
    auto tm = std::tm {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    tm.tm_sec = sec;
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

auto
wed3pm::Affairs::broadcastOnTime(const Toolkit& kit) -> void
{
    /*
        // 現在時刻を取得
        auto now = kit.getCurrentTime();

        if (nowが水曜日の15:00) {
            kit.broadcastMessage("今日は定時退社日です。計画的に業務を...\n");
        }
        auto nextTime = 次の水曜の午後3:00の時刻を計算;

        // 計算した時刻まで現スレッドをスリープ
        kit.sleepUntil(nextTime);
    */
    auto now = kit.getCurrentTime();
    auto t = std::chrono::system_clock::to_time_t(now);
    auto local = std::localtime(&t);
    if (local->tm_wday == 3
            && local->tm_hour == 15
            && local->tm_min == 0) {
        kit.broadcastMessage("今日は定時退社日です。計画的に業務を...\n");
    }
    auto today3pm = newTimePoint(local->tm_year + 1900,
        local->tm_mon + 1, local->tm_mday, 15);
    auto b = (local->tm_wday > 3
            || (local->tm_wday == 3 && local->tm_hour >= 15))
        ? 10 : 3;
    auto nextTime = today3pm + std::chrono::days(b - local->tm_wday);
    kit.sleepUntil(nextTime);
}
