cmake_minimum_required(VERSION 3.5.1)
project(exact-arithmetic)

## STD
set(CMAKE_CXX_STANDARD 17)

# HEADERS AND SOURCES
include_directories("${PROJECT_SOURCE_DIR}/headers")

# EXES
add_executable(rational-interactive src/rational-interactive src/rational src/gcd)
add_executable(rational-cmdline src/rational-cmdline src/rational src/gcd)

set_target_properties(rational-interactive
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

set_target_properties(rational-cmdline
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )

# PACKAGES #
find_package(Catch2 REQUIRED)


# TESTING
add_executable(rational-tests spec/main.cpp headers/rational.h headers/gcd.h src/rational.cpp src/gcd.cpp spec/rationals-can-be-equated.cpp spec/rationals-can-be-constructed.cpp spec/integers-can-be-converted-to-rationals.cpp spec/doubles-can-be-converted-to-rationals.cpp spec/helpers/RandomRationalGenerator.cpp spec/helpers/RandomRationalGenerator.h spec/rationals-can-be-added.cpp spec/rationals-can-be-multiplied.cpp spec/rationals-can-be-divided.cpp spec/rationals-can-be-subtracted.cpp spec/gcd-functions-correctly.cpp)
target_link_libraries(rational-tests Catch2::Catch2)

include(CTest)
include(Catch)

catch_discover_tests(rational-tests)