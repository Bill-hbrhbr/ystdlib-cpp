cmake_minimum_required(VERSION 3.22.1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")
include(ystdlib-cpp-helpers)

project(YSTDLIB_CPP LANGUAGES CXX)

set(YSTDLIB_CPP_VERSION "0.0.1" CACHE STRING "Project version.")

option(BUILD_SHARED_LIBS "Build using shared libraries." OFF)
option(YSTDLIB_CPP_BUILD_TESTING "Build the testing tree for ystdlib-cpp." ON)

# Require compiler versions that support the C++20 features necessary for compiling ystdlib-cpp
if("AppleClang" STREQUAL "${CMAKE_CXX_COMPILER_ID}")
    set(YSTDLIB_CPP_CMAKE_CXX_COMPILER_MIN_VERSION "16")
elseif("Clang" STREQUAL "${CMAKE_CXX_COMPILER_ID}")
    set(YSTDLIB_CPP_CMAKE_CXX_COMPILER_MIN_VERSION "16")
elseif("GNU" STREQUAL "${CMAKE_CXX_COMPILER_ID}")
    set(YSTDLIB_CPP_CMAKE_CXX_COMPILER_MIN_VERSION "11")
else()
    message(
        FATAL_ERROR
        "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}. Please use AppleClang, Clang, or GNU."
    )
endif()
if("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS "${YSTDLIB_CPP_CMAKE_CXX_COMPILER_MIN_VERSION}")
    message(
        FATAL_ERROR
        "${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION} is too low. Must be at \
        least ${YSTDLIB_CPP_CMAKE_CXX_COMPILER_MIN_VERSION}."
    )
endif()

# Enable exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL
    "Enable/Disable output of compile commands during generation."
    FORCE
)

if(YSTDLIB_CPP_IS_TOP_LEVEL)
    # Include dependency settings if the project isn't being included as a subproject.
    # NOTE: We mark the file optional because if the user happens to have the dependencies
    # installed, this file is not necessary.
    include("build/deps/cmake-settings/settings.cmake" OPTIONAL)

    # If previously undefined, `BUILD_TESTING` will be set to ON.
    include(CTest)
endif()

if(BUILD_TESTING AND YSTDLIB_CPP_BUILD_TESTING)
    set(YSTDLIB_CPP_ENABLE_TESTS ON)
endif()

find_package(Boost REQUIRED)
if(Boost_FOUND)
    message(STATUS "Found Boost ${Boost_VERSION}.")
endif()

if(YSTDLIB_CPP_ENABLE_TESTS)
    find_package(Catch2 3.8.0 REQUIRED)
    if(Catch2_FOUND)
        message(STATUS "Found Catch2 ${Catch2_VERSION}.")
    else()
        message(FATAL_ERROR "Could not find libraries for Catch2.")
    endif()
    include(Catch)

    # Set up the unified unit test target
    set(UNIFIED_UNIT_TEST_TARGET "unit-test-all")
    add_executable(${UNIFIED_UNIT_TEST_TARGET})
    target_link_libraries(${UNIFIED_UNIT_TEST_TARGET} PRIVATE Catch2::Catch2WithMain)
    target_compile_features(${UNIFIED_UNIT_TEST_TARGET} PRIVATE cxx_std_20)
    set_property(
        TARGET
            ${UNIFIED_UNIT_TEST_TARGET}
        PROPERTY
            RUNTIME_OUTPUT_DIRECTORY
                ${CMAKE_BINARY_DIR}/testbin
    )
    catch_discover_tests(${UNIFIED_UNIT_TEST_TARGET} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/testbin)
endif()

add_subdirectory(src/ystdlib)
