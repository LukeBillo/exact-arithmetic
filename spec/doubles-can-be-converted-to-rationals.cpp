#include <catch2/catch.hpp>
#include <dividebyzeroerror.h>
#include "rational.h"

using ExactArithmetic::Rational;
using ExactArithmetic::DivideByZeroError;

SCENARIO("Doubles can be converted to rationals", "[rational]") {
    GIVEN("Any double") {
        // todo: use take extensions to add to test cases (both double and int)
        double i = GENERATE(-1, 0, 1, 2, 3, 4, 5);

        WHEN("Calling the conversion constructor") {
            Rational converted = Rational(i);

            THEN("The integer is correctly represented as a rational") {
                REQUIRE(converted == Rational(i, 1));
            }
        }

        WHEN("Implicitly converting int to Rational") {
            Rational converted = (Rational) i;

            THEN("The integer is correctly implicitly converted") {
                REQUIRE(converted == Rational(i, 1));
            }
        }
    }
}