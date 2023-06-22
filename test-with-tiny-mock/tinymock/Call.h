#ifndef tinymock_Call_H
#define tinymock_Call_H

#include <any>
#include <optional>
#include <vector>
#include <stdexcept>
#include <source_location>
#include "Parameters.h"

namespace tinymock {

    template<typename T> class Call final {
    private:
        void (T::*function)();
        std::string name;
        std::optional<std::any> maybeReturnValue;
        std::vector<std::any> parameterList;

    public:
        Call(void (T::*function)(), const char *name):
            function(function), name(name) {
        }

        template<typename U> auto assertEquals(U actualFunction,
                const std::source_location& w
                    = std::source_location::current()) const -> Parameters {
            using namespace std::literals;

            static_assert(std::is_member_function_pointer<U>::value);
            auto actual = reinterpret_cast<void (T::*)()>(actualFunction);
            if (function != actual) {
                auto m = "assertion failed: function mismatched: "s
                    + "expected="s + toString(name) + ", "s
                    + "actual="s + toString(std::string {w.function_name()});
                throw std::runtime_error(m);
            }
            return Parameters {parameterList};
        }

        template<typename U> auto getReturnValue() const -> U {
            if (!maybeReturnValue.has_value()) {
                throw std::runtime_error(
                    "assertion failed: no return value");
            }
            return std::any_cast<U>(maybeReturnValue.value());
        }

        template<typename U> auto with(U value) const -> Call {
            auto newCall { *this };
            newCall.parameterList.push_back(std::make_any<U>(value));
            return newCall;
        }

        template<typename U> auto returning(U value) const -> Call {
            auto newCall { *this };
            newCall.maybeReturnValue
                = std::make_optional(std::make_any<U>(value));
            return newCall;
        }
    };

}

#endif
