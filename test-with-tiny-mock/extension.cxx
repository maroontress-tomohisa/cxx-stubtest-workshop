#include <chrono>
#include "tinymock/namespace.h"

template <>
auto tinymock::toString(std::chrono::system_clock::time_point p)
        -> std::string {
    auto t = std::chrono::system_clock::to_time_t(p);
    auto local = std::localtime(&t);
    auto s = std::ostringstream {}
        << std::put_time(local, "%c");
    return s.str();
}
