#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be compared", "[integer]") {
    GIVEN("Integers have an operator< implementation") {
        Integer smaller = GENERATE(take(20, random(0, 1000)));
        Integer larger = GENERATE(take(20, random(1001, 10000)));

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
}