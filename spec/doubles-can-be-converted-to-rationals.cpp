#include <catch2/catch.hpp>
#include <dividebyzeroerror.h>
#include "rational.h"

using ExactArithmetic::Rational;
using ExactArithmetic::DivideByZeroError;

using namespace Catch::Generators;

SCENARIO("Doubles can be converted to rationals", "[rational]") {
    GIVEN("Any double") {
        double i = GENERATE(take(10, random(-10.0l, 10.0l)));

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