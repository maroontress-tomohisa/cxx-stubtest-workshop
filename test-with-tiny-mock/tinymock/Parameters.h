#ifndef tinymock_Parameters_H
#define tinymock_Parameters_H

#include <any>
#include <queue>
#include <stdexcept>
#include "namespace.h"

namespace tinymock {

    class Parameters final {
    private:
        std::queue<std::any> parameterQueue;

    public:
        Parameters(const std::vector<std::any> &parameterList) {
            for (const auto& p: parameterList) {
                parameterQueue.push(p);
            }
        }

        template<typename U> auto assertEquals(U arg) -> Parameters& {
            using namespace std::literals;

            if (parameterQueue.empty()) {
                throw std::runtime_error("assertion failed: "
                    "number of parameters mismatched");
            }
            auto expectedParameter = parameterQueue.front();
            parameterQueue.pop();
            auto expectedValue = std::any_cast<U>(expectedParameter);
            if (expectedValue != arg) {
                auto m = "assertion failed: parameter mismatched, "s
                    + "expected="s + toString(expectedValue) + ", "s
                    + "actual="s + toString(arg);
                throw std::runtime_error(m);
            }
            return *this;
        }

        auto assertEmpty() const -> void {
            if (!parameterQueue.empty()) {
                throw std::runtime_error("assertion failed: "
                    "number of parameters mismatched");
            }
        }
    };

}

#endif

