cpp_library(
    NAME io_interface
    NAMESPACE ystdlib
    PUBLIC_HEADERS
        IoErrorCode.hpp
        WriterInterface.hpp
    PRIVATE_SOURCES
        IoErrorCode.cpp
        WriterInterface.cpp
    TESTS_SOURCES
        test/test_WriterInterface.cpp
)

