#include <catch2/catch.hpp>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be constructed", "[integer]") {
    GIVEN("An integer has a default constructor") {
        WHEN("constructing the integer") {
            Integer defaultInteger = Integer();

            THEN("An integer of value 0 is constructed") {
                REQUIRE(defaultInteger.toString() == "0");
                REQUIRE(defaultInteger.toInt() == 0);
            }
        }
    }

    GIVEN("An integer has a ulong long int constructor") {
        WHEN("Constructing the integer") {
            // unfortunately, the default constructor accepts only ints,
            // hence int32 max - not int64.

            unsigned long long int ullInt = GENERATE(take(10, random(0, INT32_MAX)));
            Integer constructedInteger = Integer(ullInt);

            THEN("The integer is successfully constructed") {
                REQUIRE(constructedInteger.toInt64() == ullInt);
                REQUIRE(constructedInteger.toString() == std::to_string(ullInt));
            }
        }

        WHEN("Constructing an integer with UINT64_MAX") {
            // check 64-bit integer support, since only int32 is
            // tested above.

            Integer constructedInteger = Integer(UINT64_MAX);

            THEN("The integer is successfully constructed") {
                REQUIRE(constructedInteger.toInt64() == UINT64_MAX);
                REQUIRE(constructedInteger.toString() == std::to_string(UINT64_MAX));
            }
        }
    }

    GIVEN("An integer has a std::string constructor") {
        WHEN("Constructing the integer") {
            unsigned long long int ullInt = GENERATE(take(10, random(0, INT32_MAX)));
            auto stringified = std::to_string(ullInt);

            Integer constructedInteger = Integer(stringified);

            THEN("The integer is successfully constructed") {
                REQUIRE(constructedInteger.toInt64() == ullInt);
                REQUIRE(constructedInteger.toString() == stringified);
            }
        }

        WHEN("Constructing with the string \"999999999999999999999999\"") {
            auto stringified = "999999999999999999999999";
            Integer constructedInteger = Integer(stringified);

            THEN("The integer is successfully constructed") {
                REQUIRE(constructedInteger.toString() == stringified);
            }
        }

        WHEN("Constructing with non-numeric strings") {
            auto randomString = GENERATE(as<std::string>{}, "abc", "twentyone", "two1", "-");

            THEN("An invalid argument exception is thrown") {
                REQUIRE_THROWS_AS(Integer(randomString), std::invalid_argument);
            }
        }

        WHEN("Constructing 0001 as a string") {
            auto stringified = "0001";
            Integer constructed = Integer(stringified);

            THEN("The integer is successfully constructed") {
                INFO("Integer constructed from string 0001: " << constructed)

                REQUIRE(constructed.toString() == "1");
                REQUIRE(constructed.toInt() == 1);
            }
        }
    }
}