#ifndef YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
#define YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP

#include <sys/types.h>

#include <concepts>
#include <cstddef>
#include <exception>
#include <string>
#include <type_traits>

#include "IoErrorCode.hpp"

namespace ystdlib::io_interface {
/**
 * Concept that defines an integer-based value type.
 *
 * TODO: move this into a general ystdlib-cpp typing library.
 * @tparam Type
 */
template <typename T>
concept IntType = requires(T type) {
    {
        static_cast<std::underlying_type_t<T>>(type)
    } -> std::convertible_to<int>;
};

class WriterInterface {
public:
    // Types
    class OperationFailed : public std::exception {
    public:
        // Constructor
        OperationFailed([[maybe_unused]] IoErrorCode error_code) {}
    };

    // Constructor
    WriterInterface() = default;

    // Delete copy constructor and assignment operator
    WriterInterface(WriterInterface const&) = delete;
    auto operator=(WriterInterface const&) -> WriterInterface& = delete;

    // Default move constructor and assignment operator
    WriterInterface(WriterInterface&&) noexcept = default;
    auto operator=(WriterInterface&&) noexcept -> WriterInterface& = default;

    // Destructor
    virtual ~WriterInterface() = default;

    // Methods
    /**
     * Writes the given data to the underlying medium
     * @param data
     * @param data_length
     */
    virtual auto write(char const* data, size_t data_length) -> void = 0;

    virtual auto flush() -> void = 0;

    [[nodiscard]] virtual auto try_seek_from_begin(size_t pos) -> IoErrorCode = 0;

    [[nodiscard]] virtual auto try_seek_from_current(off_t offset) -> IoErrorCode = 0;

    [[nodiscard]] virtual auto try_get_pos(size_t& pos) const -> IoErrorCode = 0;

    /**
     * Writes a numeric value
     * @param val Value to write
     */
    template <IntType T>
    auto write_numeric_value(T value) -> void;

    /**
     * Writes a character to the underlying medium
     * @param c
     */
    auto write_char(char c) -> void;
    /**
     * Writes a string to the underlying medium
     * @param str
     */
    auto write_string(std::string const& str) -> void;

    /**
     * Seeks from the beginning to the given position
     * @param pos
     */
    auto seek_from_begin(size_t pos) -> void;

    /**
     * Offsets from the current position by the given amount
     * @param offset
     */
    auto seek_from_current(off_t offset) -> void;

    /**
     * Gets the current position of the write head
     * @return Position of the write head
     */
    [[nodiscard]] auto get_pos() const -> size_t;
};

template <IntType T>
auto WriterInterface::write_numeric_value(T value) -> void {
    write(static_cast<char*>(&value), sizeof(value));
}
}  // namespace ystdlib::io_interface

#endif  // YSTDLIB_IO_INTERFACE_WRITERINTERFACE_HPP
