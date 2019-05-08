#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be compared with the greater than operator", "[integer]") {
    GIVEN("Integers have an operator> implementation") {
        Integer smaller = GENERATE(take(10, random(0, 1000)));
        Integer larger = GENERATE(take(10, random(1001, 10000)));

        WHEN("Comparing two integers where the right is larger") {
            bool leftIsLarger = smaller > larger;

            THEN("False is returned") {
                INFO("Compared: " << smaller.toString() << " > " << larger.toString())
                REQUIRE_FALSE(leftIsLarger);
            }
        }

        WHEN("Comparing two integers where the left is larger") {
            bool leftIsLarger = larger > smaller;

            THEN("True is returned") {
                INFO("Compared: " << larger.toString() << " > " << smaller.toString())
                REQUIRE(leftIsLarger);
            }
        }

        WHEN("Comparing two integers that are equal") {
            bool leftIsLarger = smaller > smaller;

            THEN("False is returned") {
                INFO("Compared: " << smaller.toString() << " > " << smaller.toString())
                REQUIRE_FALSE(leftIsLarger);
            }
        }
    }

    GIVEN("Integers have an operator>= implementation") {
        Integer smaller = GENERATE(take(10, random(0, 1000)));
        Integer larger = GENERATE(take(10, random(1001, 10000)));

        WHEN("Comparing two integers where the right is larger") {
            bool leftIsLargerOrEqual = smaller >= larger;

            THEN("False is returned") {
                INFO("Compared: " << smaller.toString() << " >= " << larger.toString())
                REQUIRE_FALSE(leftIsLargerOrEqual);
            }
        }

        WHEN("Comparing two integers where the left is larger") {
            bool leftIsLargerOrEqual = larger >= smaller;

            THEN("True is returned") {
                INFO("Compared: " << larger.toString() << " >= " << smaller.toString())
                REQUIRE(leftIsLargerOrEqual);
            }
        }

        WHEN("Comparing two integers that are equal") {
            bool leftIsLargerOrEqual = smaller >= smaller;

            THEN("True is returned") {
                INFO("Compared: " << smaller.toString() << " >= " << smaller.toString())
                REQUIRE(leftIsLargerOrEqual);
            }
        }
    }
}