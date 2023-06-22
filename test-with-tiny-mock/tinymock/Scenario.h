#ifndef tinymock_Scenario_H
#define tinymock_Scenario_H

#include "Call.h"

namespace tinymock {

    template<typename T> class Scenario final {
    private:
        std::deque<Call<T>> callQueue;

    public:
        Scenario(const std::deque<Call<T>>& callQueue): callQueue(callQueue) {
        }

        auto nextCall() -> Call<T> {
            if (callQueue.empty()) {
                throw std::runtime_error(
                    "assertion failed: number of calls mismatched");
            }
            auto call = callQueue.front();
            callQueue.pop_front();
            return call;
        }

        auto assertEmpty() -> void {
            if (!callQueue.empty()) {
                throw std::runtime_error(
                    "assertion failed: call queue is not empty");
            }
        }
    };

}

#endif
