#ifndef tinymock_namespace_H
#define tinymock_namespace_H

#include <string>
#include <iostream>
#include <iomanip>

namespace tinymock {

    template <typename U>
    std::string toString(U b) {
        if constexpr (std::is_null_pointer<U>::value) {
            return "nullptr";
        } else if constexpr (std::is_same<U, bool>::value) {
            return b ? "true" : "false";
        } else if constexpr (std::is_pointer<U>::value) {
            if (b == nullptr) {
                return "nullptr";
            }
            auto s = std::ostringstream {};
            s << std::hex << (const void *)b;
            return s.str();
        } else if constexpr (std::is_same<U, std::string>::value) {
            auto s = std::ostringstream {};
            s << '"' << b << '"';
            return s.str();
        } else if constexpr (std::is_same<U, int>::value
                || std::is_same<U, std::size_t>::value) {
            return std::to_string(b);
        } else if constexpr (std::is_same<U, char>::value) {
            auto s = std::ostringstream {}
                << "'" << b << "'";
            return s.str();
        } else {
            return "(unknown)";
        }
    }

}

#endif
