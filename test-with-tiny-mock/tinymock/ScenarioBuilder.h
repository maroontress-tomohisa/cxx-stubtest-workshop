#ifndef tinymock_ScenarioBuilder_H
#define tinymock_ScenarioBuilder_H

#include <type_traits>
#include <functional>
#include <deque>
#include "Scenario.h"
#include "Call.h"

namespace tinymock {

    template<typename T> class ScenarioBuilder final {
    private:
        std::deque<Call<T>> callQueue;

    public:
        auto add(const Call<T>& call) -> ScenarioBuilder& {
            callQueue.push_back(call);
            return *this;
        }

        template<typename U> auto lastCallReturns(U value) -> void {
            auto& call = callQueue.back();
            auto newCall = call.returning(value);
            callQueue.pop_back();
            callQueue.push_back(newCall);
        }

        auto build() const -> Scenario<T> {
            return Scenario {callQueue};
        }

        auto newCall(const std::source_location& w
                = std::source_location::current()) const {
            auto name = w.function_name();
            return [name]<typename U>(U function) {
                static_assert(std::is_member_function_pointer<U>::value);
                auto p = reinterpret_cast<void (T::*)()>(function);
                return Call<T> {p, name};
            };
        }
    };

}

#endif
