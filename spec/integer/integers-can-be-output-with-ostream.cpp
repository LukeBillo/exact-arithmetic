#include <catch2/catch.hpp>
#include <sstream>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be output using ostream", "[integer]") {
    GIVEN("An existing integer") {
        unsigned long long int randomInt = GENERATE(take(10, random(0, INT32_MAX)));
        Integer integer = Integer(randomInt);

        WHEN("Outputting the integer to a stringstream") {
            std::stringstream ss;
            ss << integer;

            THEN("The integer is output correctly") {
                std::string stringified = ss.str();
                INFO("Converted integer " << randomInt << " to " << stringified)

                REQUIRE(stringified == integer.toString());
                REQUIRE(stringified == std::to_string(randomInt));
            }
        }
    }
}