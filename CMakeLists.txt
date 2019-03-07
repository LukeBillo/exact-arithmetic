cmake_minimum_required(VERSION 3.5.1)
project(exact-arithmetic)

## STD
set(CMAKE_CXX_STANDARD 17)

# HEADERS AND SOURCES
include_directories("${PROJECT_SOURCE_DIR}/headers")

# PACKAGES #
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

# EXES
add_executable(rational-interactive src/rational-interactive src/rational src/gcd)
add_executable(rational-cmdline src/rational-cmdline src/rational src/gcd)