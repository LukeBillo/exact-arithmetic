#include <catch2/catch.hpp>
#include <dividebyzeroerror.h>
#include "rational.h"

using ExactArithmetic::Rational;
using ExactArithmetic::DivideByZeroError;

using namespace Catch::Generators;

SCENARIO("Integers can be converted to rationals", "[rational]") {
    GIVEN("Any integer") {
        int i = GENERATE(take(10, random(-10, 10)));

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