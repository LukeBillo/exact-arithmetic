#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be equated", "[integer]") {
    unsigned long long int randomInt = GENERATE(take(10, random(0, INT32_MAX)));

    GIVEN("That the operator== is overloaded") {
        WHEN("Equating equal integers with operator==") {
            Integer first = Integer(randomInt);
            Integer second = Integer(randomInt);

            THEN("True is returned") {
                bool integersAreEqual = first == second;
                REQUIRE(integersAreEqual);
            }
        }

        WHEN("Equating non-equal integers with operator==") {
            // Since the generator can never go over UINT32_MAX, just compare against UINT64_MAX
            // here, that way there's never a case where they're equal.

            Integer first = Integer(randomInt);
            Integer second = Integer(UINT64_MAX);

            THEN("False is returned") {
                bool integersAreEqual = first == second;
                REQUIRE_FALSE(integersAreEqual);
            }
        }
    }

    GIVEN("That the operator!= is overloaded") {
        WHEN("Checking equal integers with operator!=") {
            Integer first = Integer(randomInt);
            Integer second = Integer(randomInt);

            THEN("False is returned") {
                bool integersAreNotEqual = first != second;
                REQUIRE_FALSE(integersAreNotEqual);
            }
        }

        WHEN("Checking non-equal integers with operator!=") {
            Integer first = Integer(randomInt);
            Integer second = Integer(UINT64_MAX);

            THEN("True is returned") {
                bool integersAreNotEqual = first != second;
                REQUIRE(integersAreNotEqual);
            }
        }
    }
}