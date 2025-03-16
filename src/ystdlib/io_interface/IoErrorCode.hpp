#ifndef YSTDLIB_IO_INTERFACE_IOERRORCODE_HPP
#define YSTDLIB_IO_INTERFACE_IOERRORCODE_HPP

#include <cstdint>

#include <ystdlib/error_handling/ErrorCode.hpp>

namespace ystdlib::io_interface {
enum class IoErrorCodeEnum : uint8_t {
    Success = 0
};

using IoErrorCode = ystdlib::error_handling::ErrorCode<IoErrorCodeEnum>;
using IoErrorCategory = ystdlib::error_handling::ErrorCategory<IoErrorCodeEnum>;
}  // namespace ystdlib::io_interface

YSTDLIB_ERROR_HANDLING_MARK_AS_ERROR_CODE_ENUM(ystdlib::io_interface::IoErrorCodeEnum);

#endif  // YSTDLIB_IO_INTERFACE_IOERRORCODE_HPP

