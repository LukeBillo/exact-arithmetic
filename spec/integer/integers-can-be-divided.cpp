#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be divided", "[integer]") {
    GIVEN("Integers have the operator/= implemented") {
        unsigned long long int randomInt = GENERATE(take(10, random(1, INT32_MAX / 2)));
        Integer randomInteger = Integer(randomInt);

        WHEN("Dividing an existing integer by a random integer") {
            unsigned long long int existingInt = GENERATE(take(10, random(0, INT32_MAX / 2)));
            Integer existingInteger = Integer(existingInt);

            INFO("Divided " << existingInteger << " /= " << randomInteger)

            THEN("The integers are added correctly") {
                Integer &result = existingInteger /= randomInteger;
                Integer expected = Integer(existingInt / randomInt);


                REQUIRE(existingInteger == expected);
                REQUIRE(result == expected);
            }
        }
    }
}