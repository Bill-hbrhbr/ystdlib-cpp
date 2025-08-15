# Used for CMake toolchain setup. Sets `VAR_NAME` to `BINARY_PATH` after verifying the toolchain
# binary exists. Stops configuration if the required binary is missing.
#
# @param {string} VAR_NAME Variable name to set.
# @param {string} BINARY_PATH Path to the CMake toolchain binary.
function(set_toolchain_binary_var VAR_NAME BINARY_PATH)
    if(NOT EXISTS "${BINARY_PATH}")
        message(FATAL_ERROR "Required CMake toolchain binary not found: ${BINARY_PATH}")
    endif()
    set(${VAR_NAME} "${BINARY_PATH}" PARENT_SCOPE)
endfunction()

message(STATUS "Setting up LLVM v15 toolchain...")

execute_process(
    COMMAND
        "brew" "--prefix" "llvm@15"
    RESULT_VARIABLE BREW_RESULT
    OUTPUT_VARIABLE LLVM_TOOLCHAIN_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(NOT 0 EQUAL BREW_RESULT)
    message(
        FATAL_ERROR
        "Failed to locate LLVM v15 using Homebrew. Please ensure llvm@15 is installed: 'brew"
        " install llvm@15'"
    )
endif()

set_toolchain_binary_var(CMAKE_C_COMPILER "${LLVM_TOOLCHAIN_PREFIX}/bin/clang")
set_toolchain_binary_var(CMAKE_CXX_COMPILER "${LLVM_TOOLCHAIN_PREFIX}/bin/clang++")
set_toolchain_binary_var(CMAKE_AR "${LLVM_TOOLCHAIN_PREFIX}/bin/llvm-ar")
set_toolchain_binary_var(CMAKE_RANLIB "${LLVM_TOOLCHAIN_PREFIX}/bin/llvm-ranlib")
