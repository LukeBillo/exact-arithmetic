#include <catch2/catch.hpp>
#include <sstream>
#include "integer.h"

using ExactArithmetic::Integer;

SCENARIO("Integers can be input using istream", "[integer]") {
    GIVEN("An existing integer") {
        unsigned long long int randomInt = GENERATE(take(10, random(0, INT32_MAX)));
        std::stringstream ss;
        ss << randomInt;

        WHEN("Inputting the integer from a stringstream") {
            Integer integer = Integer();
            ss >> integer;

            THEN("The integer is output correctly") {
                INFO("Converted integer " << randomInt << " to " << integer)

                REQUIRE(integer.toInt() == randomInt);
                REQUIRE(integer.toString() == ss.str());
            }
        }
    }
}