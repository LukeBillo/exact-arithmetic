cmake_minimum_required(VERSION 3.5.1)
project(exact-arithmetic)

## STD
set(CMAKE_CXX_STANDARD 17)

# HEADERS AND SOURCES
include_directories("${PROJECT_SOURCE_DIR}/headers")

# EXES
add_executable(rational-interactive src/rational-interactive src/rational src/gcd)
add_executable(rational-cmdline src/rational-cmdline src/rational src/gcd)

# PACKAGES #
find_package(Catch2 REQUIRED)


# TESTING
add_executable(rational-tests headers/rational.h headers/gcd.h src/rational.cpp src/gcd.cpp test/rationals-can-be-equated.cpp test/main.cpp)
target_link_libraries(rational-tests Catch2::Catch2)

include(CTest)
include(Catch)

catch_discover_tests(rational-tests)