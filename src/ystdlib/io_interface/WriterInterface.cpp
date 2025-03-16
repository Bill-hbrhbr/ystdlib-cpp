#include "WriterInterface.hpp"

#include <sys/types.h>

#include <cstddef>
#include <string>

#include "IoErrorCode.hpp"

namespace ystdlib::io_interface {
auto WriterInterface::write_char(char c) -> void {
    write(&c, 1);
}

auto WriterInterface::write_string(std::string const& str) -> void {
    write(str.c_str(), str.length());
}

auto WriterInterface::seek_from_begin(size_t pos) -> void {
    auto const error_code{try_seek_from_begin(pos)};
    if (IoErrorCodeEnum::Success != error_code.get_error()) {
        throw OperationFailed(error_code);
    }
}

auto WriterInterface::seek_from_current(off_t offset) -> void {
    auto const error_code{try_seek_from_current(offset)};
    if (IoErrorCodeEnum::Success != error_code.get_error()) {
        throw OperationFailed(error_code);
    }
}

auto WriterInterface::get_pos() const -> size_t {
    size_t pos{0};
    auto const error_code{try_get_pos(pos)};
    if (IoErrorCodeEnum::Success != error_code.get_error()) {
        throw OperationFailed(error_code);
    }
    return pos;
}
}  // namespace ystdlib::io_interface
