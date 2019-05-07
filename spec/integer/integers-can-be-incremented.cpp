#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be incremented", "[integer]") {
    GIVEN("Integers have pre-increment operator++ implemented") {
        WHEN("Pre-incrementing an existing integer") {
            // INT32_MAX - 1 here so that never overflows; this would break the REQUIRE()
            unsigned long long int randomInt = GENERATE(take(20, random(0, INT32_MAX - 1)));

            Integer integer = Integer(randomInt);
            Integer& result = ++integer;

            THEN("The integer is incremented successfully") {
                auto expected = std::to_string(randomInt + 1);

                REQUIRE(integer.toString() == expected);
                REQUIRE(result.toString() == expected);
            }
        }

        WHEN("Pre-incrementing UINT64_MAX") {
            Integer uint64Max = Integer(UINT64_MAX);
            Integer& result = ++uint64Max;

            THEN("The integer is incremented successfully") {
                // this is UINT64_MAX + 1 as a string.
                std::string expected = "18446744073709551616";

                REQUIRE(uint64Max.toString() == expected);
                REQUIRE(result.toString() == expected);
            }
        }

        WHEN("Pre-incrementing 9999999999999999") {
            Integer ridiculousInteger = Integer("9999999999999999");
            Integer& result = ++ridiculousInteger;

            THEN("The integer is incremented successfully") {
                std::string expected = "10000000000000000";

                REQUIRE(ridiculousInteger.toString() == expected);
                REQUIRE(result.toString() == expected);
            }
        }
    }

    GIVEN("Integers have post-increment operator++ implemented") {
        WHEN("Post-incrementing an existing integer") {
            // INT32_MAX - 1 here so that never overflows; this would break the REQUIRE()
            unsigned long long int randomInt = GENERATE(take(20, random(0, INT32_MAX - 1)));

            Integer integer = Integer(randomInt);
            Integer result = integer++;

            THEN("The integer is incremented successfully") {
                auto expected_integer = std::to_string(randomInt + 1);
                auto expected_result = std::to_string(randomInt);

                REQUIRE(integer.toString() == expected_integer);
                REQUIRE(result.toString() == expected_result);
            }
        }

        WHEN("Post-incrementing UINT64_MAX") {
            Integer uint64Max = Integer(UINT64_MAX);
            Integer result = uint64Max++;

            THEN("The integer is incremented successfully") {
                // this is UINT64_MAX + 1 as a string.
                std::string expected_integer = "18446744073709551616";
                std::string expected_result = std::to_string(UINT64_MAX);

                REQUIRE(uint64Max.toString() == expected_integer);
                REQUIRE(result.toString() == expected_result);
            }
        }

        WHEN("Post-incrementing 9999999999999999") {
            Integer ridiculousInteger = Integer("9999999999999999");
            Integer result = ridiculousInteger++;

            THEN("The integer is incremented successfully") {
                std::string expected_integer = "10000000000000000";
                std::string expected_result = "9999999999999999";

                REQUIRE(ridiculousInteger.toString() == expected_integer);
                REQUIRE(result.toString() == expected_result);
            }
        }
    }
}