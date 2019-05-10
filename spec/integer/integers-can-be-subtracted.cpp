#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be subtracted", "[integer]") {
    GIVEN("Integers have the operator-= implemented") {
        unsigned long long int randomInt = GENERATE(take(10, random(0, 5000)));
        Integer randomInteger = Integer(randomInt);

        WHEN("Subtracting random integers to an existing integer") {
            unsigned long long int existingInt = GENERATE(take(10, random(5000, 10000)));
            Integer existingInteger = Integer(existingInt);

            INFO("Subtracting " << existingInteger << " -= " << randomInteger)

            THEN("The integers are subtracted correctly") {
                Integer &result = existingInteger -= randomInteger;
                Integer expected = Integer(existingInt - randomInt);


                REQUIRE(existingInteger == expected);
                REQUIRE(result == expected);
            }
        }

        WHEN("Subtracting UINT64_MAX and 1") {
            Integer existingInteger = Integer(UINT64_MAX);

            INFO("Subtracting " << existingInteger << " -= " << 1)

            THEN("The integers are subtracted correctly") {
                Integer &result = existingInteger -= 1;

                // this is UINT64_MAX + 1 as a string.
                std::string expected_integer = "18446744073709551614";


                REQUIRE(existingInteger.toString() == expected_integer);
                REQUIRE(result.toString() == expected_integer);
            }
        }

        WHEN("Adding 0 and a random integer") {
            Integer zero = Integer();

            THEN("The integers are subtracted correctly") {
                Integer &result = zero -= randomInteger;

                INFO("Subtracted " << 0 << " -= " << randomInteger)

                // Since the randomInteger was added to zero,
                // the expected result is equal to randomInteger.
                REQUIRE(zero == 0);
                REQUIRE(result == 0);
            }
        }

        WHEN("Subtracting 1001001 and 2002") {
            Integer existing = Integer(1001001);
            Integer subtraction = Integer(2002);

            THEN("the integers are subtracted successfully") {
                Integer expected = Integer(1001001 - 2002);
                existing -= subtraction;

                REQUIRE(existing == expected);
            }
        }
    }
}