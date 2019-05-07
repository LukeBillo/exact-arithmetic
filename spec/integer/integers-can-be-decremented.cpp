#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be decremented", "[integer]") {
    GIVEN("Integers have pre-decrement operator-- implemented") {
        WHEN("Pre-decrementing an existing integer") {
            // Start at 1 here, since 0 does not get decremented currently
            unsigned long long int randomInt = GENERATE(take(20, random(1, INT32_MAX)));

            Integer integer = Integer(randomInt);
            Integer& result = --integer;

            THEN("The integer is decremented successfully") {
                auto expected = std::to_string(randomInt - 1);

                REQUIRE(integer.toString() == expected);
                REQUIRE(result.toString() == expected);
            }
        }

        WHEN("Pre-decrementing UINT64_MAX") {
            Integer uint64Max = Integer(UINT64_MAX);
            Integer& result = --uint64Max;

            THEN("The integer is decremented successfully") {
                std::string expected = std::to_string(UINT64_MAX - 1);

                REQUIRE(uint64Max.toString() == expected);
                REQUIRE(result.toString() == expected);
            }
        }

        WHEN("Pre-decrementing 0") {
            Integer zero = Integer();
            Integer& result = --zero;

            THEN("The integer is not decremented") {
                std::string expected = std::to_string(0);

                REQUIRE(zero.toString() == expected);
                REQUIRE(result.toString() == expected);
            }
        }

        WHEN("Pre-decrementing 9999999999999999") {
            Integer ridiculousInteger = Integer("9999999999999999");
            Integer& result = --ridiculousInteger;

            THEN("The integer is decremented successfully") {
                std::string expected = "9999999999999998";

                REQUIRE(ridiculousInteger.toString() == expected);
                REQUIRE(result.toString() == expected);
            }
        }
    }

    GIVEN("Integers have post-decrement operator-- implemented") {
        WHEN("Post-decrementing an existing integer") {
            unsigned long long int randomInt = GENERATE(take(20, random(1, INT32_MAX)));

            Integer integer = Integer(randomInt);
            Integer result = integer--;

            THEN("The integer is decremented successfully") {
                auto expected_integer = std::to_string(randomInt - 1);
                auto expected_result = std::to_string(randomInt);

                REQUIRE(integer.toString() == expected_integer);
                REQUIRE(result.toString() == expected_result);
            }
        }

        WHEN("Post-decrementing UINT64_MAX") {
            Integer uint64Max = Integer(UINT64_MAX);
            Integer result = uint64Max--;

            THEN("The integer is decremented successfully") {
                std::string expected_integer = "18446744073709551614";
                std::string expected_result = std::to_string(UINT64_MAX);

                REQUIRE(uint64Max.toString() == expected_integer);
                REQUIRE(result.toString() == expected_result);
            }
        }

        WHEN("Post-decrementing 0") {
            Integer zero = Integer(0);
            Integer result = zero--;

            THEN("The integer is not decremented") {
                std::string expected = std::to_string(0);

                REQUIRE(zero.toString() == expected);
                REQUIRE(result.toString() == expected);
            }
        }

        WHEN("Post-decrementing 9999999999999999") {
            Integer ridiculousInteger = Integer("9999999999999999");
            Integer result = ridiculousInteger--;

            THEN("The integer is decremented successfully") {
                std::string expected_integer = "9999999999999998";
                std::string expected_result = "9999999999999999";

                REQUIRE(ridiculousInteger.toString() == expected_integer);
                REQUIRE(result.toString() == expected_result);
            }
        }
    }
}