#include <catch2/catch.hpp>
#include "rational.h"

SCENARIO("rationals can be equated", "[rational]") {
    GIVEN("Two rationals that are equal") {
        ExactArithmetic::Rational rational1 = ExactArithmetic::Rational(2,5);
        ExactArithmetic::Rational rational2 = ExactArithmetic::Rational(2,5);

        WHEN("Using operator== to equate them") {
            bool result = rational1 == rational2;

            THEN("True is returned") {
                REQUIRE(result);
            }
        }
    }
}