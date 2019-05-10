#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be copied", "[integer]") {
    GIVEN("Integers have a copy constructor") {
        unsigned long long int randomInt = GENERATE(take(10, random(0, INT32_MAX)));
        Integer existing = Integer(randomInt);

        WHEN("Copying an integer") {
            Integer copy = Integer(existing);

            THEN("The two integers are equal") {
                REQUIRE(copy == existing);

                copy += 1;
                REQUIRE(copy > existing);
            }
        }
    }
}