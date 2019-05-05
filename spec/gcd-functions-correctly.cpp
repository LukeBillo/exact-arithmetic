#include "gcd.h"
#include <catch2/catch.hpp>

struct TestGcd {
    int first;
    int second;
    int expected;

    TestGcd(int first, int second, int expected) : first(first), second(second), expected(expected) {}
};

using ExactArithmetic::gcd;

SCENARIO("Gcd functions correctly", "[gcd]") {
    GIVEN("Gcd is being used to find the greatest common divisor") {
        TestGcd testGcd = GENERATE(
                TestGcd(5, 10, 5),
                TestGcd(35, 10, 5),
                TestGcd(3, 7, 1),
                TestGcd(9, 33, 3),
                TestGcd(100, 434, 2),
                TestGcd(3099,3120, 3)
        );

        WHEN("Finding the greatest common divisor") {
            int actual = gcd(testGcd.first, testGcd.second);

            THEN("The correct greatest common divisor is returned") {
                REQUIRE(actual == testGcd.expected);
            }
        }
    }
}