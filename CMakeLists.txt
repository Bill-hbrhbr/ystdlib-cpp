cmake_minimum_required(VERSION 3.16.3)
project(YSTDLIB_CPP LANGUAGES CXX)

set(YSTDLIB_CPP_VERSION "0.0.1" CACHE STRING "Project version.")

# Enable exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL
    "Enable/Disable output of compile commands during generation."
    FORCE
)

# Import CMake helper functions
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/CMake)
include(ystdlib-cpp-helpers)

add_subdirectory(src/ystdlib)

# Test dummy project
add_executable(dummy)
target_sources(dummy PRIVATE src/main.cpp)
target_link_libraries(dummy PRIVATE ystdlib::testlib)
target_compile_features(dummy PRIVATE cxx_std_20)
