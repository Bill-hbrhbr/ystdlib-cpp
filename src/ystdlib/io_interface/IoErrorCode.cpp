#include "IoErrorCode.hpp"

#include <string>

using ystdlib::io_interface::IoErrorCategory;
using ystdlib::io_interface::IoErrorCodeEnum;

template <>
auto IoErrorCategory::name() const noexcept -> char const* {
    return "IoErrorCategory";
}

template <>
auto IoErrorCategory::message(IoErrorCodeEnum error_enum) const -> std::string {
    switch (error_enum) {
        case IoErrorCodeEnum::Success:
            return "Success";
        default:
            return "Unrecognized ystdlib::io_interface::IoErrorCode.";
    }
}
