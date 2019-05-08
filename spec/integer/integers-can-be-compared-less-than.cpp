#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be compared with the less than operator", "[integer]") {
    GIVEN("Integers have an operator< implementation") {
        Integer smaller = GENERATE(take(10, random(0, 1000)));
        Integer larger = GENERATE(take(10, random(1001, 10000)));

        WHEN("Comparing two integers where the left is smaller") {
            bool leftIsSmaller = smaller < larger;

            THEN("True is returned") {
                INFO("Compared: " << smaller.toString() << " < " << larger.toString())
                REQUIRE(leftIsSmaller);
            }
        }

        WHEN("Comparing two integers where the right is smaller") {
            bool leftIsSmaller = larger < smaller;

            THEN("False is returned") {
                INFO("Compared: " << larger.toString() << " < " << smaller.toString())
                REQUIRE_FALSE(leftIsSmaller);
            }
        }

        WHEN("Comparing two integers that are equal") {
            bool leftIsSmaller = smaller < smaller;

            THEN("False is returned") {
                INFO("Compared: " << smaller.toString() << " < " << smaller.toString())
                REQUIRE_FALSE(leftIsSmaller);
            }
        }
    }

    GIVEN("Integers have an operator<= implementation") {
        Integer smaller = GENERATE(take(10, random(0, 1000)));
        Integer larger = GENERATE(take(10, random(1001, 10000)));

        WHEN("Comparing two integers where the left is smaller") {
            bool leftIsSmallerOrEqual = smaller < larger;

            THEN("True is returned") {
                INFO("Compared: " << smaller.toString() << " <= " << larger.toString())
                REQUIRE(leftIsSmallerOrEqual);
            }
        }

        WHEN("Comparing two integers where the right is smaller") {
            bool leftIsSmallerOrEqual = larger < smaller;

            THEN("False is returned") {
                INFO("Compared: " << larger.toString() << " <= " << smaller.toString())
                REQUIRE_FALSE(leftIsSmallerOrEqual);
            }
        }

        WHEN("Comparing two integers that are equal") {
            bool leftIsSmallerOrEqual = smaller <= smaller;

            THEN("True is returned") {
                INFO("Compared: " << smaller.toString() << " <= " << smaller.toString())
                REQUIRE(leftIsSmallerOrEqual);
            }
        }
    }
}