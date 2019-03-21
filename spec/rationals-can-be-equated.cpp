#include <catch2/catch.hpp>
#include "rational.h"

using ExactArithmetic::Rational;

SCENARIO("Rationals can be equated", "[rational]") {
    GIVEN("Two equal rationals exist") {
        Rational rational1 = Rational(2, 3);
        Rational rational2 = Rational(2, 3);

        WHEN("Equating them using operator==") {
            bool result = rational1 == rational2;

            THEN("True is returned") {
                REQUIRE(result);
            }
        }
    }
}