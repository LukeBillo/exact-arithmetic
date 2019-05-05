#include <catch2/catch.hpp>
#include "integer.h"]

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

        }
    }
}