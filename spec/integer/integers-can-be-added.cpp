#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be added", "[integer]") {
    GIVEN("Integers have the operator+= implemented") {
        unsigned long long int randomInt = GENERATE(take(10, random(0, INT32_MAX / 2)));
        Integer randomInteger = Integer(randomInt);

        WHEN("Adding random integers to an existing integer") {
            unsigned long long int existingInt = GENERATE(take(10, random(0, INT32_MAX / 2)));
            Integer existingInteger = Integer(existingInt);

            INFO("Added " << existingInteger << " += " << randomInteger)

            THEN("The integers are added correctly") {
                Integer &result = existingInteger += randomInteger;
                Integer expected = Integer(randomInt + existingInt);


                REQUIRE(existingInteger == expected);
                REQUIRE(result == expected);
            }
        }

        WHEN("Adding UINT64_MAX and 1") {
            Integer existingInteger = Integer(UINT64_MAX);

            INFO("Added " << existingInteger << " += " << 1)

            THEN("The integers are added correctly") {
                Integer &result = existingInteger += 1;

                // this is UINT64_MAX + 1 as a string.
                std::string expected_integer = "18446744073709551616";


                REQUIRE(existingInteger.toString() == expected_integer);
                REQUIRE(result.toString() == expected_integer);
            }
        }

        WHEN("Adding 0 and a random integer") {
            Integer zero = Integer();

            THEN("The integers are added correctly") {
                Integer &result = zero += randomInteger;

                INFO("Added " << 0 << " += " << randomInteger)

                // Since the randomInteger was added to zero,
                // the expected result is equal to randomInteger.
                REQUIRE(zero == randomInteger);
                REQUIRE(result == randomInteger);
            }
        }
    }
}